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
    public partial class Month_Bad : Form
    {
        public Month_Bad()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
        }

        private void LoadData(int selectedMonth)
        {
            // DataManager.Instance에서 필요한 데이터를 가져와서 처리
            var data = DataManager.Instance;

            // 선택한 월의 불량품 생산량 계산
            var dailyNGCounts = data.Where(p => p.INSP == "NG" && p.STD_DT.Month == selectedMonth)
                                    .GroupBy(p => p.STD_DT.Day)
                                    .Select(g => new { Day = g.Key, Count = g.Count() })
                                    .OrderBy(g => g.Day)
                                    .ToList();

            // 차트 설정
            chart1.Series.Clear(); // 기존 Series를 Clear합니다.

            Series series = new Series("일별 불량")
            {
                ChartType = SeriesChartType.Line,
                BorderWidth = 3 
            };

            // 데이터 바인딩
            foreach (var item in dailyNGCounts)
            {
                series.Points.AddXY($"{item.Day}일", item.Count);
            }

            chart1.Series.Add(series);
            chart1.ChartAreas[0].AxisX.Interval = 1;
            chart1.ChartAreas[0].AxisX.Title = "일별";
            chart1.ChartAreas[0].AxisY.Title = "불량품 생산량";
            chart1.ChartAreas[0].AxisY.Minimum = 0;

            // 차트 다시 그리기
            chart1.Invalidate();
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            // ComboBox에서 선택된 월 가져오기
            int selectedMonth = comboBox1.SelectedIndex + 1; // 콤보박스 인덱스는 0부터 시작하므로 1을 더합니다.

            // 선택한 월의 데이터 로드
            LoadData(selectedMonth);
        }
    }
}
