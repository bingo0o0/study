#include <sqlite3.h>
#include <iostream>
#include <string>
#include <memory>
#include <cstring>

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
    // if (sqlite3_exec(pdb, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    // {
    //     cout << errMsg << endl;
    //     sqlite3_free(errMsg);
    //     return -1;
    // }

    sql = "insert into test (id, name) values (3, 'snow3')";
    cout << sql << endl;
    if (sqlite3_exec(pdb, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        cout << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }
    const char *pTail = nullptr;
    sql = "select * from test";
    sqlite3_stmt *pStmt = nullptr;
    int err = sqlite3_prepare_v2(pdb, sql, -1, &pStmt, &pTail);
    if (err != SQLITE_OK)
    {
        cout << sqlite3_errmsg(pdb) << endl;
        return -1;
    }

    err = sqlite3_step(pStmt);
    int ncols = sqlite3_column_count(pStmt);

    cout << "ncols: " << ncols << endl;
    while(err == SQLITE_ROW)
    {
        for (auto i=0; i<ncols; ++i)
            cout << sqlite3_column_text(pStmt, i) << "  ";
        cout << endl;

        err = sqlite3_step(pStmt);
    }
    sqlite3_finalize(pStmt);

    return 0;
}