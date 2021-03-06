#!/bin/sh

if [ $# != 5 ]; then
    echo "Usage: $0 PACKAGE VERSION CHROOT_BASE ARCHITECTURES CODES"
    echo " e.g.: $0 groonga 0.1.9 /var/lib/chroot 'i386 amd64' 'lenny unstable hardy karmic'"
    exit 1
fi

PACKAGE=$1
VERSION=$2
CHROOT_BASE=$3
ARCHITECTURES=$4
CODES=$5

PATH=/usr/local/sbin:/usr/sbin:$PATH

script_base_dir=`dirname $0`

if test "$PARALLEL" = "yes"; then
    parallel="yes"
else
    parallel="no"
fi

run()
{
    "$@"
    if test $? -ne 0; then
	echo "Failed $@"
	exit 1
    fi
}

run_sudo()
{
    run sudo "$@"
}

build_chroot()
{
    architecture=$1
    code_name=$2

    run_sudo debootstrap --arch $architecture $code_name $base_dir

    case $code_name in
	lenny|squeeze|unstable)
	    run_sudo sed -i'' -e 's/us/jp/' $base_dir/etc/apt/sources.list
	    ;;
	*)
	    run_sudo sed -i'' \
		-e 's,http://archive,http://jp.archive,' \
		-e 's/main$/main universe/' \
		$base_dir/etc/apt/sources.list
	    ;;
    esac

    run_sudo sh -c "echo >> /etc/fstab"
    run_sudo sh -c "echo /sys ${base_dir}/sys none bind 0 0 >> /etc/fstab"
    run_sudo sh -c "echo /dev ${base_dir}/dev none bind 0 0 >> /etc/fstab"
    run_sudo sh -c "echo devpts-chroot ${base_dir}/dev/pts devpts defaults 0 0 >> /etc/fstab"
    run_sudo sh -c "echo proc-chroot ${base_dir}/proc proc defaults 0 0 >> /etc/fstab"
    run_sudo mount ${base_dir}/sys
    run_sudo mount ${base_dir}/dev
    run_sudo mount ${base_dir}/dev/pts
    run_sudo mount ${base_dir}/proc
}

build()
{
    architecture=$1
    code_name=$2

    target=${code_name}-${architecture}
    base_dir=${CHROOT_BASE}/${target}
    if [ ! -d $base_dir ]; then
	run build_chroot $architecture $code_name
    fi

    case ${code_name} in
	lenny|squeeze|wheezy|unstable)
	    distribution=debian
	    component=main
	    ;;
	*)
	    distribution=ubuntu
	    component=universe
	    ;;
    esac

    source_dir=${script_base_dir}/..
    build_user=${PACKAGE}-build
    build_user_dir=${base_dir}/home/$build_user
    build_dir=${build_user_dir}/build
    pool_base_dir=${script_base_dir}/${distribution}/pool/${code_name}/${component}
    package_initial=$(echo ${PACKAGE} | sed -e 's/\(.\).*/\1/')
    pool_dir=${pool_base_dir}/${package_initial}/${PACKAGE}
    run cp $source_dir/${PACKAGE}-${VERSION}.tar.gz \
	${CHROOT_BASE}/$target/tmp/
    run rm -rf ${CHROOT_BASE}/$target/tmp/${PACKAGE}-debian
    run cp -rp $source_dir/debian/ \
	${CHROOT_BASE}/$target/tmp/${PACKAGE}-debian
    run echo $PACKAGE > ${CHROOT_BASE}/$target/tmp/build-package
    run echo $VERSION > ${CHROOT_BASE}/$target/tmp/build-version
    run echo $build_user > ${CHROOT_BASE}/$target/tmp/build-user
    run cp ${script_base_dir}/${PACKAGE}-depended-packages \
	${CHROOT_BASE}/$target/tmp/depended-packages
    run cp ${script_base_dir}/build-deb.sh \
	${CHROOT_BASE}/$target/tmp/
    sources_list_d=${CHROOT_BASE}/${target}/etc/apt/sources.list.d
    run cat <<EOF | run_sudo tee ${sources_list_d}/groonga.list
deb http://packages.groonga.org/${distribution}/ ${code_name} ${component}
deb-src http://packages.groonga.org/${distribution}/ ${code_name} ${component}
EOF
    if [ "${code_name}" = "lenny" ]; then
	run cat <<EOF | run_sudo tee ${sources_list_d}/backports.list
deb http://backports.debian.org/debian-backports lenny-backports main
deb-src http://backports.debian.org/debian-backports lenny-backports main
EOF
    fi
    run_sudo rm -rf $build_dir
    run_sudo su -c "/usr/sbin/chroot ${CHROOT_BASE}/$target /tmp/build-deb.sh"
    run mkdir -p $pool_dir
    for path in $build_dir/*; do
	[ -f $path ] && run cp -p $path $pool_dir/
    done
}

for architecture in $ARCHITECTURES; do
    for code_name in $CODES; do
	if test "$parallel" = "yes"; then
	    build $architecture $code_name &
	else
	    build $architecture $code_name
	fi;
    done
done

if test "$parallel" = "yes"; then
    wait
fi
