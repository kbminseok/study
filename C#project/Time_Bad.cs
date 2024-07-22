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
    public partial class Time_Bad : Form
    {
        public Time_Bad()
        {
            InitializeComponent();
            LoadChartData();
        }

        private void LoadChartData()
        {
            // DataManager.Instance에서 필요한 데이터를 가져와서 처리
            var data = DataManager.Instance;

            // 시간대별 불량률 계산
            Dictionary<int, double> hourlyDefectRate = new Dictionary<int, double>();

            // 모든 날짜의 해당 시간 합산
            foreach (var record in data)
            {
                int hour = record.STD_DT.Hour;
                double ngCount = record.INSP == "NG" ? 1 : 0;

                if (hourlyDefectRate.ContainsKey(hour))
                {
                    hourlyDefectRate[hour] += ngCount;
                }
                else
                {
                    hourlyDefectRate[hour] = ngCount;
                }
            }

            // 시간대별 평균 불량률 계산
            foreach (var hour in hourlyDefectRate.Keys.ToList())
            {
                double totalCount = data.Count(p => p.STD_DT.Hour == hour);
                hourlyDefectRate[hour] = (hourlyDefectRate[hour] / totalCount) * 100; // 백분율로 변환
            }

            // 차트 설정
            chart1.Series.Clear(); // 기존 Series를 Clear합니다.

            Series series = new Series("시간별 불량")
            {
                ChartType = SeriesChartType.Line, // 선 그래프로 설정합니다.
                BorderWidth = 3 // 선의 두께를 설정합니다. 여기서는 3픽셀로 설정했습니다.
            };

            // 데이터 바인딩
            foreach (var item in hourlyDefectRate.OrderBy(kvp => kvp.Key))
            {
                series.Points.AddXY($"{item.Key}시", item.Value);
            }

            chart1.Series.Add(series);
            chart1.ChartAreas[0].AxisX.Interval = 1;
            chart1.ChartAreas[0].AxisX.Title = "시간대";
            chart1.ChartAreas[0].AxisY.Title = "불량률 (%)";
            chart1.ChartAreas[0].AxisY.Minimum = 13;
            chart1.ChartAreas[0].AxisY.Maximum = 18; // Y축의 최대값을 100으로 설정하여 백분율을 표시합니다.

            // 차트 다시 그리기
            chart1.Invalidate();
        }
    }
}
