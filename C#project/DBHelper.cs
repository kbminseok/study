using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace pasteurizer
{
    public class DBHelper
    {
        private static SqlConnection conn = new SqlConnection();
        public static SqlDataAdapter da;
        public static DataSet ds;
        public static DataTable dt;
        private static string TABLENAME = " pasteurizer ";
        private static void connectDB()
        {
            string dataSource = "local";
            string db = "pasteurizer";
            string security = "SSPI";

            conn.ConnectionString = $"Data Source=({dataSource}); " +
                $"initial Catalog={db}; " +
                $"integrated Security = {security}; " +
                $"Timeout=3";
            conn = new SqlConnection(conn.ConnectionString);
            conn.Open();
        }

        public static void selectQuery()
        {
            try
            {
                connectDB();
                SqlCommand cmd = new SqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "select * from" + TABLENAME;
                da = new SqlDataAdapter(cmd);
                ds = new DataSet();
                da.Fill(ds, TABLENAME);
                dt = ds.Tables[0];
            }
            catch (Exception ex)
            {
                DataManager.printLog("select" + ex.StackTrace);
            }
            finally
            {
                conn.Close();
            }
        }
        public static void UpdatePasteurizerData(string[] updatedValues)
        {
            try
            {
                connectDB();
                string query = "UPDATE pasteurizer SET MIXA_PASTEUR_STATE = @mixAState, MIXB_PASTEUR_STATE = @mixBState, " +
                               "MIXA_PASTEUR_TEMP = @mixATemp, MIXB_PASTEUR_TEMP = @mixBTemp, " +
                               "INSP = @insp WHERE STD_DT = @stdDt";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@stdDt", DateTime.Parse(updatedValues[0]));
                cmd.Parameters.AddWithValue("@mixAState", updatedValues[1]);
                cmd.Parameters.AddWithValue("@mixBState", updatedValues[2]);
                cmd.Parameters.AddWithValue("@mixATemp", double.Parse(updatedValues[3]));
                cmd.Parameters.AddWithValue("@mixBTemp", double.Parse(updatedValues[4]));
                cmd.Parameters.AddWithValue("@insp", updatedValues[5]);
                cmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                MessageBox.Show("데이터베이스 업데이트 중 오류 발생: " + ex.Message);
            }
            finally
            {
                conn.Close();
            }
        }

        public static void InsertPasteurizerData(string param1, string param2 = null, string param3 = null, string param4 = null, string param5 = null, string param6 = null)
        {
            string sqlcmd = "";
            sqlcmd = "INSERT INTO pasteurizer " +
                "(STD_DT, MIXA_PASTEUR_STATE, MIXB_PASTEUR_STATE, MIXA_PASTEUR_TEMP, MIXB_PASTEUR_TEMP, INSP) " +
                "VALUES (@stdDt, @mixAState, @mixBState, @mixATemp, @mixBTemp, @insp)";
            try
            {
                connectDB();
                SqlCommand command = new SqlCommand();
                command.Connection = conn;
                command.Parameters.AddWithValue("@stdDt", param1);
                command.Parameters.AddWithValue("@mixAState", param2);
                command.Parameters.AddWithValue("@mixBState", param3);
                command.Parameters.AddWithValue("@mixATemp", param4);
                command.Parameters.AddWithValue("@mixBTemp", param5);
                command.Parameters.AddWithValue("@insp", param6);
                command.CommandText = sqlcmd;
                command.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                DataManager.printLog(ex.StackTrace);
                MessageBox.Show("데이터베이스 업데이트 중 오류 발생: " + ex.Message);
            }
            finally
            {
                conn.Close();
                MessageBox.Show("추가 되었습니다.");
            }
        }

        public static void DeletePasteurizerData(string stdDt)
        {
            try
            {
                connectDB();
                string query = "DELETE FROM pasteurizer WHERE STD_DT = @stdDt";
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.Parameters.AddWithValue("@stdDt", DateTime.Parse(stdDt).ToString("yyyy-MM-dd HH:mm"));
                cmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                MessageBox.Show("데이터베이스 삭제 중 오류 발생: " + ex.Message);
            }
            finally
            {
                conn.Close();
            }
        }


    }
}
