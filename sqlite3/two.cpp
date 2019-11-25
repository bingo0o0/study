#include <sqlite3.h>
#include <iostream>
#include <string>
#include <memory>

using namespace std;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Not find db file name\n";
        return -1;
    }

    sqlite3 *pdb;
    if (sqlite3_open(argv[1], &pdb) != SQLITE_OK)
    {
        cerr << "connect to db " << argv[1] << " failed\n";
        return -1;
    }
    shared_ptr<sqlite3> spDB(pdb, [](sqlite3 *p) {sqlite3_close(p);} );

    char *errMsg = nullptr;
    const char *sql = "create table test (id int primary key, name text)";
    if (sqlite3_exec(pdb, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        cout << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }

    sql = "insert into test (id, name) values (1, 'snow')";
    cout << sql << endl;
    if (sqlite3_exec(pdb, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        cout << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }

    char **tableRzt = nullptr;
    int nRow, nColu;
    sql = "select * from test";
    if (sqlite3_get_table(pdb, sql, &tableRzt, &nRow, &nColu, &errMsg) != SQLITE_OK)
    {
        cout << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }

    cout << nRow << " " << nColu << endl;
    for (auto i=0; i < (nRow+1)*nColu; ++i)
    {
        if (i%nColu == 0)
            cout << endl;

        cout << tableRzt[i] << "        ";
    }
    sqlite3_free_table(tableRzt);

    return 0;
}