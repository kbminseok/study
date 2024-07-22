using System;
using System.Data;
using System.Linq;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.IO;
using pasteurizer;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Collections.Generic;

namespace PasteurizerApp
{
    public partial class Main : Form
    {
        private string[] selectedCellValues; // 선택한 셀의 데이터를 저장할 배열

        public Main()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
            dataGridView1.CellClick += dataGridView1_CellClick; // CellClick 이벤트 핸들러 등록
        }


        private void InitializeScreen()
        {
            comboBox1.SelectedIndex = -1; // 선택된 항목 없음으로 설정
            dataGridView1.DataSource = null;
            chart1.Series.Clear();
        }

        private void MonthPrint_Click(object sender, EventArgs e)
        {
            DataManager.Load();
            dataGridView1.DataSource = null;
            dataGridView1.DataSource = DataManager.Instance;

            int selectedMonth = comboBox1.SelectedIndex + 1; // 콤보박스 인덱스는 0부터 시작하므로 3을 더해줍니다.
            var filteredData = DataManager.Instance.Where(p => p.STD_DT.Month == selectedMonth).ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = filteredData;

            UpdateChart(filteredData);
        }

        private void AllPrint_Click(object sender, EventArgs e)
        {
            DataManager.Load();
            dataGridView1.DataSource = null;
            dataGridView1.DataSource = DataManager.Instance;

            var allData = DataManager.Instance;
            UpdateChart(allData);
        }

        private void button_good_Click(object sender, EventArgs e)
        {
            var filteredData = DataManager.Instance.Where(item =>
                double.TryParse(item.MIXB_PASTEUR_TEMP, out double mixBPasteurTemp) &&
                double.TryParse(item.MIXA_PASTEUR_TEMP, out double mixAPasteurTemp) &&
                mixBPasteurTemp > 619.5 &&
                mixAPasteurTemp <= 579.5
            ).ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = filteredData;
            UpdateChart(filteredData);
        }

        private void button_bad_Click(object sender, EventArgs e)
        {
            var filteredData = DataManager.Instance.Where(item =>
                double.TryParse(item.MIXB_PASTEUR_TEMP, out double mixBPasteurTemp) &&
                double.TryParse(item.MIXA_PASTEUR_TEMP, out double mixAPasteurTemp) &&
                mixBPasteurTemp > 619.5 &&
                mixAPasteurTemp > 579.5
            ).ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = filteredData;
            UpdateChart(filteredData);
        }

        private void reset_Click(object sender, EventArgs e)
        {
            InitializeScreen();
        }

        private void csv_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog
            {
                Filter = "CSV files (*.csv)|*.csv|All files (*.*)|*.*",
                FilterIndex = 1,
                RestoreDirectory = true
            };

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog1.FileName;

                try
                {
                    DataTable dt = new DataTable();
                    using (StreamReader sr = new StreamReader(filePath))
                    {
                        string[] headers = sr.ReadLine().Split(',');
                        foreach (string header in headers)
                        {
                            dt.Columns.Add(header);
                        }

                        while (!sr.EndOfStream)
                        {
                            string[] rows = sr.ReadLine().Split(',');
                            if (rows.Any(string.IsNullOrWhiteSpace))
                                continue;

                            DataRow dr = dt.NewRow();
                            for (int i = 0; i < headers.Length; i++)
                            {
                                dr[i] = rows[i];
                            }
                            dt.Rows.Add(dr);
                        }
                    }

                    dataGridView1.DataSource = dt;
                    BindDataToChart(dt);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
                if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
                {
                    DataGridViewRow selectedRow = dataGridView1.Rows[e.RowIndex];
                    selectedCellValues = new string[6];
                    selectedCellValues[0] = selectedRow.Cells[0].Value?.ToString();
                    selectedCellValues[1] = selectedRow.Cells[1].Value?.ToString();
                    selectedCellValues[2] = selectedRow.Cells[2].Value?.ToString();
                    selectedCellValues[3] = selectedRow.Cells[3].Value?.ToString();
                    selectedCellValues[4] = selectedRow.Cells[4].Value?.ToString();
                    selectedCellValues[5] = selectedRow.Cells[5].Value?.ToString();
                }
        }

        private void modify_Click(object sender, EventArgs e)
        {
            if (selectedCellValues != null && selectedCellValues.Length >= 5)
            {
                Modify form2 = new Modify(selectedCellValues);
                form2.DataUpdated += Form2_DataUpdated; // 이벤트 핸들러 추가
                form2.ShowDialog(); // 모달 창으로 열기
            }
            else
            {
                MessageBox.Show("먼저 DataGridView에서 셀을 클릭해주세요.");
            }
        }

        private void UpdateChart(List<Pasteurizer> data)
        {
            chart1.Series.Clear();
            Series series = new Series("Data");
            series.ChartType = SeriesChartType.Pie;

            int okCount = data.Count(p => p.INSP == "OK");
            int ngCount = data.Count(p => p.INSP == "NG");
            int totalCount = okCount + ngCount;

            series.Points.AddXY("양품", okCount);
            series.Points.AddXY("불량품", ngCount);

            series.Points[0].Label = $"{okCount} ({((double)okCount / totalCount * 100):F2}%)";
            series.Points[1].Label = $"{ngCount} ({((double)ngCount / totalCount * 100):F2}%)";
            series.Points[0].LegendText = "양품";
            series.Points[1].LegendText = "불량품";

            chart1.Series.Add(series);
        }

        private void BindDataToChart(DataTable dt)
        {
            chart1.Series.Clear();
            Series series = new Series("Data");
            series.ChartType = SeriesChartType.Pie;

            int ngCount = dt.AsEnumerable().Count(row => row.Field<string>("INSP") == "NG");
            int okCount = dt.AsEnumerable().Count(row => row.Field<string>("INSP") == "OK");
            int totalCount = okCount + ngCount;

            series.Points.AddXY("OK", okCount);
            series.Points.AddXY("NG", ngCount);

            series.Points[0].Label = $"{okCount} ({((double)okCount / totalCount * 100):F2}%)";
            series.Points[1].Label = $"{ngCount} ({((double)ngCount / totalCount * 100):F2}%)";

            chart1.Series.Add(series);
        }

        private void Form2_DataUpdated(string[] updatedValues)
        {
            // 업데이트된 데이터 처리 로직
            // 예: DataGridView 갱신 또는 DataManager 업데이트
            if (updatedValues.Length >= 5)
            {
                int selectedRowIndex = dataGridView1.CurrentCell.RowIndex;
                for (int i = 0; i < dataGridView1.Columns.Count; i++)
                {
                    dataGridView1.Rows[selectedRowIndex].Cells[i].Value = updatedValues[i];
                }
            }
        }

        private async void csv_up_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "CSV Files (*.csv)|*.csv|All Files (*.*)|*.*";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                try
                {
                    await CsvDataHandler.InsertDataFromCsvAsync(filePath);
                    MessageBox.Show("업로드가 완료되었습니다.", "성공", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"파일 업로드 중 오류가 발생했습니다:\n{ex.Message}", "오류", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void delete_Click(object sender, EventArgs e)
        {
            if (selectedCellValues != null && selectedCellValues.Length >= 5)
            {
                // 메시지 박스를 표시하고 사용자의 응답을 확인합니다.
                DialogResult result = MessageBox.Show("정말 삭제하시겠습니까?", "확인", MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                {
                    DBHelper.DeletePasteurizerData(selectedCellValues[0]);
                }
            }
            else
            {
                MessageBox.Show("먼저 DataGridView에서 셀을 클릭해주세요.");
            }
        }

        private void insert_Click(object sender, EventArgs e)
        {
            Insert form3 = new Insert();
            form3.ShowDialog();
        }

        private void button_Month_Click(object sender, EventArgs e)
        {
            Month_Bad form4 = new Month_Bad();
            form4.ShowDialog();
        }

        private void button_hour_Click(object sender, EventArgs e)
        {
            Time_Bad form5 = new Time_Bad();
            form5.ShowDialog();
        }

        private void temperature_Click(object sender, EventArgs e)
        {
            status form6 = new status();
            form6.ShowDialog();
        }

        private void status_Click(object sender, EventArgs e)
        {
            //전체 데이터 산포도 출력 코드
            DataManager.Load();
            temperature form7 = new temperature(DataManager.Instance);
            form7.ShowDialog();
        }
    }
}
