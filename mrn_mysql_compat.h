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

#ifndef _mrn_mysql_compat_h
#define _mrn_mysql_compat_h

#if MYSQL_VERSION_ID >= 50500
#  define my_free(PTR, FLAG) my_free(PTR)
#endif

#ifndef HA_INPLACE_ADD_INDEX_NO_READ_WRITE
#  define HA_INPLACE_ADD_INDEX_NO_READ_WRITE         HA_ONLINE_ADD_INDEX_NO_WRITES
#  define HA_INPLACE_DROP_INDEX_NO_READ_WRITE        HA_ONLINE_DROP_INDEX_NO_WRITES
#  define HA_INPLACE_ADD_UNIQUE_INDEX_NO_READ_WRITE  HA_ONLINE_ADD_UNIQUE_INDEX_NO_WRITES
#  define HA_INPLACE_DROP_UNIQUE_INDEX_NO_READ_WRITE HA_ONLINE_DROP_UNIQUE_INDEX_NO_WRITES
#  define HA_INPLACE_ADD_PK_INDEX_NO_READ_WRITE      HA_ONLINE_ADD_PK_INDEX_NO_WRITES
#  define HA_INPLACE_DROP_PK_INDEX_NO_READ_WRITE     HA_ONLINE_DROP_PK_INDEX_NO_WRITES

#  define HA_INPLACE_ADD_INDEX_NO_WRITE              HA_ONLINE_ADD_INDEX
#  define HA_INPLACE_DROP_INDEX_NO_WRITE             HA_ONLINE_DROP_INDEX
#  define HA_INPLACE_ADD_UNIQUE_INDEX_NO_WRITE       HA_ONLINE_ADD_UNIQUE_INDEX
#  define HA_INPLACE_DROP_UNIQUE_INDEX_NO_WRITE      HA_ONLINE_DROP_UNIQUE_INDEX
#  define HA_INPLACE_ADD_PK_INDEX_NO_WRITE           HA_ONLINE_ADD_PK_INDEX
#  define HA_INPLACE_DROP_PK_INDEX_NO_WRITE          HA_ONLINE_DROP_PK_INDEX
#endif

#if MYSQL_VERSION_ID < 50600
  typedef Item COND;
#endif

#if MYSQL_VERSION_ID < 50603 || defined(MRN_MYSQL_INNODB_FTS_P)
  typedef MYSQL_ERROR Sql_condition;
#endif

#if MYSQL_VERSION_ID >= 50516 && MYSQL_VERSION_ID < 50603
#  define MRN_PLUGIN_HAVE_FLAGS 1
#endif

#ifndef MRN_MARIADB_P
  typedef char *range_id_t;
#endif

#endif /* _mrn_mysql_compat_h */
