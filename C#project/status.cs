using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace pasteurizer
{
    public partial class status : Form
    {
        public status()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DataManager.Load();
            var allData = DataManager.Instance;
            ChartUpdate(allData);
        }

        private void ChartUpdate(List<Pasteurizer> data)
        {
            if (comboBox2.SelectedItem != null)
            {
                string selectedInsp = comboBox2.SelectedItem.ToString();
                int selectedMonth = comboBox1.SelectedIndex + 1;

                if (!(selectedMonth == 0))
                {
                    var filteredData = data.Where(item => item.INSP == selectedInsp && item.STD_DT.Month == selectedMonth).ToList();

                    chart1.Series.Clear();
                    Series mixA_series = new Series("mixA_temp");
                    mixA_series.ChartType = SeriesChartType.Line;
                    mixA_series.Color = Color.Blue;
                    mixA_series.BorderWidth = 2;

                    Series mixB_series = new Series("mixB_temp");
                    mixB_series.ChartType = SeriesChartType.Line;
                    mixB_series.Color = Color.Red;
                    mixB_series.BorderWidth = 2;

                    foreach (var item in filteredData)
                    {
                        if (int.TryParse(item.MIXA_PASTEUR_TEMP, out int mixA_temp))
                            mixA_series.Points.AddXY(item.STD_DT, mixA_temp);
                        if (int.TryParse(item.MIXB_PASTEUR_TEMP, out int mixB_temp))
                            mixB_series.Points.AddXY(item.STD_DT, mixB_temp);
                    }
                    chart1.Series.Add(mixA_series);
                    chart1.Series.Add(mixB_series);

                    chart1.ChartAreas[0].AxisX.LabelStyle.Format = "yyyy-MM-dd HH:mm";
                    chart1.ChartAreas[0].AxisX.Title = "Time";
                    chart1.ChartAreas[0].AxisY.Title = "Temperature";
                    chart1.Legends[0].Enabled = true;

                    chart1.DataBind();
                }
                else
                    MessageBox.Show("출력하고 싶은 달을 선택하세요");
            }
            else
                MessageBox.Show("출력하고 싶은 상태를 선택하세요");

        }
    }
}
