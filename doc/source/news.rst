.. highlightlang:: none

News
====

.. _release-1-11:

Release 1.11 - ????/??/??
-------------------------

Improvements
^^^^^^^^^^^^

Fixes
^^^^^

* [storage mode] fix a bug that full text search on a table without primary key returns empty results #1193.

.. _release-1-10:

Release 1.10 - 2011/11/29
-------------------------

Since this release, this project and product is called
"mroonga" instead of "groonga storage engine".

This release introduces MariaDB support and fixes several bugs.

Improvements
^^^^^^^^^^^^

* rename to "mroonga" from "groonga storage engine". #1170
* add groonga_libgroonga_version and groonga_version variables. #1158
* information_schema.plugins.plugin_version returns mroonga's version. #1157
* add groonga_log_file variable. #1178 [Suggested by nobody]
* FLUSH STATUS flushes groonga_* status variables. #1166 [Reported by Kazuhiko]
* support TRUNCATE TABLE #1151. [Suggested by Takahiro Nagai]
* support ALTER TABLE #1168.
* support MariaDB 5.2.9. #1152 [Reported by Kazuhiko]
* support MariaDB 5.3.2-beta. #1152 [Reported by Kazuhiko]
* [rpm] split document package.
* improve memory allocation for string system variables.
* use PLUGIN_LICENSE_GPL. [Suggested by Kazuhiko]
* remove needless MeCab related configurations.
* support FOUND_ROWS() and SQL_CALC_FOUND_ROWS. #1163 [Reported by Horikoshi Yuki]
* support table name that contains '-'. #1165 [Reported by nobody]
* support inplace index change on MySQL 5.1.
* [deb] support i386.
* [rpm] support i386.

Fixes
^^^^^

* [storage mode] fix a bug that REPLACE INTO with TEXT column does not work. #1153 [Reported by Kazuhiko]
* [wrapper mode] fix a bug that INSERT inside LOCK TABLE does not work with InnoDB. #1154 [Reported by Kazuhiko]
* fix a bug that using ORDER and LIMIT returns a wrong result. #1161 [Reported by Horikoshi Yuki]
* fix a crash bug when FORCE INDEX with unknown key is used. #1181 [Reported by Takahiro Nagai]

Thanks
^^^^^^

* Kazuhiko
* Horikoshi Yuki
* nobody
* Takahiro Nagai

.. _release-1-0-1:

Release 1.0.1 - 2011/10/29
--------------------------

The important changes in this release are the enhancement of geolocation search and the improvement of dynamic index modification in storage mode.

Improvements
^^^^^^^^^^^^

* [storage mode][wrapper mode] support reopening a database by `flush tables`.
* [wrapper mode] support geolocation index. (Only Point type can be stored in a column. Search using index is only available for MBRContains).
* [benchmark] add `groonga_dry_write` variable to specify not to write to groonga database, that is useful to check bottle necks in benchmarks.
* mention MySQL version in the installation guide for CentOS 6. [proposed by @yoshi_ken]
* [geolocation] improve performance by skip needless processes.
* add  `--disable-fast-mutexes` configure option to ignore fast mutexes even if mysql_config says it is enabled.
* [storage mode] support `create index`.
* [storage mode] support `drop index`.
* [storage mode] support multi columns index for full text search.
* support `D` pragma.
* support MySQL 5.5.17.
* support MySQL 5.6.3-m6.
* support groonga 1.2.7. (1.2.6 or below are no longer supported).
* support Ubuntu 11.10 Oneiric Ocelot.

Fixes
^^^^^

* fix a bug that we have no results if we specify '+' at the beginning of the query in boolean mode. [reported by Hajime Nishiyama]
* [Fedora] fix package dependencies. [reported by Takahiro Nagai]
* [Fedora] fix a problem that we get undefined symbol error when the plugin is loaded. [reported by Takahiro Nagai]
* [storage mode] fix a bug that index will not be correctly created if `varchar` is used in a multi-column index. #1143 [reported by Takahiro Nagai]

Thanks
^^^^^^

* @yoshi_ken
* Hajime Nishiyama
* Takahiro Nagai

.. _release-1-0-0:

1.0.0 リリース - 2011/09/29
---------------------------

初回リリースから約1年経って、初のメジャーリリース！

改良
^^^^

* [ラッパーモード] drop index対応。 #1040
* [ストレージモード] GEOMETRY対応。（ただし、カラムに保存できる型はPointのみ対応。インデックスを利用した位置検索はMBRContainsのみ対応。） #1041
* [ストレージモード] マルチカラムインデックスに対応。 #455
* [ストレージモード][ラッパーモード] 全文検索用パーサー（トークナイザー）のカスタマイズに対応。 #592
* configureにデフォルトの全文検索用パーサーを指定する `--with-default-parser` オプションを追加。
* 実行時にデフォルトの全文検索用パーサーを指定する `groonga_default_parser` 変数を追加。
* [ラッパーモード] ストレージモードで実装している `order` と `limit` が指定された場合に必要のないレコードを返さないようにする高速化に対応。
* [ストレージモード] 1つの `select` 中での複数の `match against` 指定に対応。
* [非互換][ストレージモード] `_score` カラムの削除。代わりにMySQL標準の書き方である `match against` を使ってください。
* [ラッパーモード] プライマリキーの更新に対応。
* MySQL 5.5.16に対応。
* CentOS 6に対応。
* groonga 1.2.6に対応。（1.2.5以下のサポートを削除。）

修正
^^^^

* [Ubuntu] Lucid上でインストールエラーが発生する問題を修正。 （Isao Sugimotoさんが報告）
* auto_incrementを使った場合にテキストデータが壊れる問題を修正。 （@zaubermaerchenさんが報告） #1072
* [Ubuntu] Lucid上でテーブルを削除するとクラッシュする問題を修正。 #1063 （Isao Sugimotoさんが報告）
* MySQLと同じビルドオプションを使っていなかった問題を修正。 GitHub#4 (groongaのGitHubのIssues) （Tomohiro MITSUMUNEさんが報告）

感謝
^^^^

* Isao Sugimotoさん
* @zaubermaerchenさん
* Tomohiro MITSUMUNEさん

Past releases
-------------

.. toctree::
   :maxdepth: 2

   news/0.x
