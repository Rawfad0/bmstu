using Npgsql;

public class TestDapperContext : DapperContext
{
    public TestDapperContext() : base("Host=localhost;Port=5432;Database=marketplace_db_test;Username=marketplace_user;Password=1;Include Error Detail=true;") { }
}
