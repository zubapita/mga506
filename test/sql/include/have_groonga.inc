# Copyright(C) 2010 Tetsuro IKEDA
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

disable_query_log;

if (!`SELECT 1 FROM information_schema.plugins WHERE plugin_name = "groonga"`)
{
  INSTALL PLUGIN groonga SONAME 'ha_groonga.so';
  INSTALL PLUGIN groonga_stats SONAME 'ha_groonga.so';
}

let have_default_storage_engine_variable=`SELECT 1 FROM information_schema.global_variables WHERE variable_name = "default_storage_engine"`;
if ($have_default_storage_engine_variable)
{
  set default_storage_engine=groonga;
}
if (!$have_default_storage_engine_variable)
{
  set storage_engine=groonga;
}

enable_query_log;
