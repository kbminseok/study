using System;
using System.Data.SqlClient;
using System.IO;
using System.Threading.Tasks;

namespace pasteurizer
{
    public static class CsvDataHandler
    {
        public static async Task InsertDataFromCsvAsync(string filePath)
        {
            //서버 이름 변경 필요
            string connectionString = "Data Source=localhost;Initial Catalog=pasteurizer;Integrated Security=True;";
            string[] lines = File.ReadAllLines(filePath);

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                await conn.OpenAsync();

                foreach (var line in lines)
                {
                    var values = line.Split(',');

                    try
                    {
                        string query = "INSERT INTO pasteurizer (STD_DT, MIXA_PASTEUR_STATE, MIXB_PASTEUR_STATE, MIXA_PASTEUR_TEMP, MIXB_PASTEUR_TEMP, INSP) " +
                                       "VALUES (@STD_DT, @MIXA_PASTEUR_STATE, @MIXB_PASTEUR_STATE, @MIXA_PASTEUR_TEMP, @MIXB_PASTEUR_TEMP, @INSP)";

                        using (SqlCommand cmd = new SqlCommand(query, conn))
                        {
                            cmd.Parameters.AddWithValue("@STD_DT", DateTime.Parse(values[0]));
                            cmd.Parameters.AddWithValue("@MIXA_PASTEUR_STATE", values[1]);
                            cmd.Parameters.AddWithValue("@MIXB_PASTEUR_STATE", values[2]);
                            cmd.Parameters.AddWithValue("@MIXA_PASTEUR_TEMP", values[3]);
                            cmd.Parameters.AddWithValue("@MIXB_PASTEUR_TEMP", values[4]);
                            cmd.Parameters.AddWithValue("@INSP", values[5]);

                            await cmd.ExecuteNonQueryAsync();
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Error processing line: {line}. Error: {ex.Message}");
                    }
                }
            }
        }
    }
}
