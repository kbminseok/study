using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pasteurizer
{
    public class DataManager
    {
        //싱글톤 : 단 하나의 인스턴스를 모두 다 돌려쓰는 것

        public static List<Pasteurizer> Instance = new List<Pasteurizer>();
        static DataManager() 
        {
            Load();
        }

        public static void Load()
        {
            try
            {
                DBHelper.selectQuery();
                Instance.Clear();
                foreach (DataRow item in DBHelper.dt.Rows)
                {
                    Pasteurizer i = new Pasteurizer();

                    // STD_DT 공백 처리
                    string stdDtString = item["STD_DT"].ToString();
                    i.STD_DT = !string.IsNullOrWhiteSpace(stdDtString) ? DateTime.Parse(stdDtString) : DateTime.MinValue;

                    // MIXA_PASTEUR_STATE가 공백이 아닐 때만 값을 읽어옵니다.
                    if (!string.IsNullOrWhiteSpace(item["MIXA_PASTEUR_STATE"].ToString()))
                    {
                        i.MIXA_PASTEUR_STATE = item["MIXA_PASTEUR_STATE"].ToString();
                    }

                    // MIXB_PASTEUR_STATE가 공백이 아닐 때만 값을 읽어옵니다.
                    if (!string.IsNullOrWhiteSpace(item["MIXB_PASTEUR_STATE"].ToString()))
                    {
                        i.MIXB_PASTEUR_STATE = item["MIXB_PASTEUR_STATE"].ToString();
                    }

                    // MIXA_PASTEUR_TEMP가 공백이 아닐 때만 값을 읽어옵니다.
                    if (!string.IsNullOrWhiteSpace(item["MIXA_PASTEUR_TEMP"].ToString()))
                    {
                        double mixAPasteurTemp;
                        if (double.TryParse(item["MIXA_PASTEUR_TEMP"].ToString(), out mixAPasteurTemp) && mixAPasteurTemp < 5000)
                        {
                            i.MIXA_PASTEUR_TEMP = mixAPasteurTemp.ToString();
                        }
                    }

                    // MIXB_PASTEUR_TEMP가 공백이 아닐 때만 값을 읽어옵니다.
                    if (!string.IsNullOrWhiteSpace(item["MIXB_PASTEUR_TEMP"].ToString()))
                    {
                        double mixBPasteurTemp;
                        if (double.TryParse(item["MIXB_PASTEUR_TEMP"].ToString(), out mixBPasteurTemp) && mixBPasteurTemp < 5000)
                        {
                            i.MIXB_PASTEUR_TEMP = mixBPasteurTemp.ToString();
                        }
                    }

                    // INSP 공백 처리
                    i.INSP = item["INSP"].ToString();

                    // 모든 속성이 공백이 아니고, 입력된 숫자가 5000 미만인 경우에만 추가합니다.
                    if (!string.IsNullOrWhiteSpace(i.STD_DT.ToString()) &&
                        !string.IsNullOrWhiteSpace(i.MIXA_PASTEUR_STATE) &&
                        !string.IsNullOrWhiteSpace(i.MIXB_PASTEUR_STATE) &&
                        !string.IsNullOrWhiteSpace(i.MIXA_PASTEUR_TEMP) &&
                        !string.IsNullOrWhiteSpace(i.MIXB_PASTEUR_TEMP) &&
                        !string.IsNullOrWhiteSpace(i.INSP))
                    {
                        Instance.Add(i);
                    }

                }
            }
            catch (Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.Message);
                System.Windows.Forms.MessageBox.Show(ex.StackTrace);

            }
        }

        public static void printLog(string v)
        {
            DirectoryInfo di = new DirectoryInfo("pHistory");
            if (di.Exists == false)
                di.Create(); //해당 폴더 없으면 새로 만듦
            using (StreamWriter w = new StreamWriter(@"pHistory\pHistory.txt", true))
            {
                string now = $"[{DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff")}]";
                w.WriteLine(now + v);
            }
        }

    }
}
