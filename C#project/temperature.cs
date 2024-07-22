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
    public partial class temperature : Form
    {
        private List<Pasteurizer> _data;
        public temperature(List<Pasteurizer> data)
        {
            InitializeComponent();
            _data = data;

            Chart1.Click += showChart_Click;
        }

        private void CreateChart(List<Pasteurizer> data)
        {
            // 차트 폼 생성
            var chart = new Chart { Dock = DockStyle.Fill };

            // 차트 영역 설정
            var chartArea = new ChartArea();
            chart.ChartAreas.Add(chartArea);

            // 양품 데이터 시리즈 생성
            var goodSeries = new Series
            {
                Name = "Good Products",
                ChartType = SeriesChartType.Point,
                Color = System.Drawing.Color.Red
            };

            // 불량 데이터 시리즈 생성
            var badSeries = new Series
            {
                Name = "Bad Products",
                ChartType = SeriesChartType.Point,
                Color = System.Drawing.Color.Black
            };

            // 데이터를 양품과 불량으로 분리하여 추가
            foreach (var record in data)
            {
                if (record.INSP == "OK")
                {
                    goodSeries.Points.AddXY(record.MIXA_PASTEUR_TEMP, record.MIXB_PASTEUR_TEMP);
                }
                else if (record.INSP == "NG")
                {
                    badSeries.Points.AddXY(record.MIXA_PASTEUR_TEMP, record.MIXB_PASTEUR_TEMP);
                }
            }

            chart.Series.Add(goodSeries);
            chart.Series.Add(badSeries);

            // 차트 제목 설정
            chart.Titles.Add("Machine A Temperature vs. Machine B Temperature");

            // 축 라벨 설정
            chartArea.AxisX.Title = "Machine A Temperature";
            chartArea.AxisY.Title = "Machine B Temperature";

            // 범례 추가
            chart.Legends.Add(new Legend("Legend"));

            Controls.Add(chart);
        }

        private void showChart_Click(object sender, EventArgs e)
        {
            // 차트를 표시하기 전에 기존 차트를 제거하여 중복 생성 방지
            foreach (var control in this.Controls.OfType<Chart>().ToList())
            {
                this.Controls.Remove(control);
                control.Dispose();
            }
            // 새로운 차트 생성
            CreateChart(_data);
        }

        private void close_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
