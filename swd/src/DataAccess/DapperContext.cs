using Npgsql;
using Dapper;

public class DapperContext : IDisposable
{
    private readonly string _connectionString;
    private readonly NpgsqlConnection _connection;

    public DapperContext(string connectionString)
    {
        _connectionString = connectionString;
        _connection = new NpgsqlConnection(_connectionString);
        _connection.Open();
    }

    public NpgsqlConnection Connection => _connection;

    public void Dispose()
    {
        _connection.Close();
        _connection.Dispose();
    }
}
