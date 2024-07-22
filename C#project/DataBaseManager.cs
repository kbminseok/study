using System;
using System.Data;
using System.Data.SqlClient;

namespace pasteurizer
{
    public class DatabaseManager
    {
        private string _connectionString;

        public DatabaseManager(string connectionString)
        {
            _connectionString = connectionString;
        }

        public void InsertData(string tableName, Pasteurizer data)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(_connectionString))
                {
                    connection.Open();
                    string query = $"INSERT INTO {tableName} (STD_DT, MIXA_PASTEUR_STATE, MIXB_PASTEUR_STATE, MIXA_PASTEUR_TEMP, MIXB_PASTEUR_TEMP, INSP) " +
                                   "VALUES (@STD_DT, @MIXA_PASTEUR_STATE, @MIXB_PASTEUR_STATE, @MIXA_PASTEUR_TEMP, @MIXB_PASTEUR_TEMP, @INSP)";
                    SqlCommand command = new SqlCommand(query, connection);
                    command.Parameters.AddWithValue("@STD_DT", data.STD_DT);
                    command.Parameters.AddWithValue("@MIXA_PASTEUR_STATE", data.MIXA_PASTEUR_STATE);
                    command.Parameters.AddWithValue("@MIXB_PASTEUR_STATE", data.MIXB_PASTEUR_STATE);
                    command.Parameters.AddWithValue("@MIXA_PASTEUR_TEMP", data.MIXA_PASTEUR_TEMP);
                    command.Parameters.AddWithValue("@MIXB_PASTEUR_TEMP", data.MIXB_PASTEUR_TEMP);
                    command.Parameters.AddWithValue("@INSP", data.INSP);

                    command.ExecuteNonQuery();
                }
            }
            catch (Exception ex)
            {
                DataManager.printLog("select" + ex.StackTrace);
                throw;
            }
        }

        public DataTable GetData(string tableName)
        {
            DataTable dataTable = new DataTable();
            try
            {
                using (SqlConnection connection = new SqlConnection(_connectionString))
                {
                    connection.Open();
                    string query = $"SELECT * FROM {tableName}";
                    SqlDataAdapter adapter = new SqlDataAdapter(query, connection);
                    adapter.Fill(dataTable);
                }
            }
            catch (Exception ex)
            {
                DataManager.printLog("select" + ex.StackTrace);
                throw;
            }

            return dataTable;
        }
    }
}
