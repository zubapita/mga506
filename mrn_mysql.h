/* -*- c-basic-offset: 2 -*- */
/*
  Copyright(C) 2011 Kouhei Sutou <kou@clear-code.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _mrn_mysql_h
#define _mrn_mysql_h

#ifdef HAVE_CONFIG_H
#  include "config.h"
/* We need to undefine them because my_config.h defines them. :< */
#  undef VERSION
#  undef PACKAGE
#  undef PACKAGE_BUGREPORT
#  undef PACKAGE_NAME
#  undef PACKAGE_STRING
#  undef PACKAGE_TARNAME
#  undef PACKAGE_VERSION
#endif

#include "mrn_version.h"

#ifdef FORCE_FAST_MUTEX_DISABLED
#  ifdef MY_PTHREAD_FASTMUTEX
#    undef MY_PTHREAD_FASTMUTEX
#  endif
#endif

#define MYSQL_SERVER 1
#include <mysql_version.h>

#if MYSQL_VERSION_ID < 50500
#  include <mysql_priv.h>
#  include <mysql/plugin.h>
#else
#  include <sql_priv.h>
#  include <sql_class.h>
#  include <probes_mysql.h>
#  include <sql_partition.h>
#endif

#ifdef MARIADB_BASE_VERSION
#  define MRN_MARIADB_P 1
#endif

#define MRN_DBUG_ENTER_FUNCTION() DBUG_ENTER(__FUNCTION__)

#endif /* _mrn_mysql_h */
