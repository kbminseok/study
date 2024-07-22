namespace PasteurizerApp
{
    partial class Main
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.MonthPrint = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.AllPrint = new System.Windows.Forms.Button();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.button_good = new System.Windows.Forms.Button();
            this.button_bad = new System.Windows.Forms.Button();
            this.reset = new System.Windows.Forms.Button();
            this.csv = new System.Windows.Forms.Button();
            this.modify = new System.Windows.Forms.Button();
            this.csv_up = new System.Windows.Forms.Button();
            this.insert = new System.Windows.Forms.Button();
            this.delete = new System.Windows.Forms.Button();
            this.button_Month = new System.Windows.Forms.Button();
            this.button_hour = new System.Windows.Forms.Button();
            this.temperature = new System.Windows.Forms.Button();
            this.status = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // MonthPrint
            // 
            this.MonthPrint.Location = new System.Drawing.Point(471, 78);
            this.MonthPrint.Name = "MonthPrint";
            this.MonthPrint.Size = new System.Drawing.Size(75, 20);
            this.MonthPrint.TabIndex = 0;
            this.MonthPrint.Text = "월별출력";
            this.MonthPrint.UseVisualStyleBackColor = true;
            this.MonthPrint.Click += new System.EventHandler(this.MonthPrint_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(12, 104);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(660, 200);
            this.dataGridView1.TabIndex = 1;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12"});
            this.comboBox1.Location = new System.Drawing.Point(552, 78);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 20);
            this.comboBox1.TabIndex = 2;
            // 
            // AllPrint
            // 
            this.AllPrint.Location = new System.Drawing.Point(12, 75);
            this.AllPrint.Name = "AllPrint";
            this.AllPrint.Size = new System.Drawing.Size(75, 23);
            this.AllPrint.TabIndex = 3;
            this.AllPrint.Text = "전체출력";
            this.AllPrint.UseVisualStyleBackColor = true;
            this.AllPrint.Click += new System.EventHandler(this.AllPrint_Click);
            // 
            // chart1
            // 
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chart1.Legends.Add(legend1);
            this.chart1.Location = new System.Drawing.Point(12, 310);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Pie;
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(660, 178);
            this.chart1.TabIndex = 3;
            this.chart1.Text = "chart1";
            // 
            // button_good
            // 
            this.button_good.Location = new System.Drawing.Point(12, 13);
            this.button_good.Name = "button_good";
            this.button_good.Size = new System.Drawing.Size(93, 23);
            this.button_good.TabIndex = 4;
            this.button_good.Text = "양품온도기준";
            this.button_good.UseVisualStyleBackColor = true;
            this.button_good.Click += new System.EventHandler(this.button_good_Click);
            // 
            // button_bad
            // 
            this.button_bad.Location = new System.Drawing.Point(111, 12);
            this.button_bad.Name = "button_bad";
            this.button_bad.Size = new System.Drawing.Size(96, 23);
            this.button_bad.TabIndex = 5;
            this.button_bad.Text = "불량온도기준";
            this.button_bad.UseVisualStyleBackColor = true;
            this.button_bad.Click += new System.EventHandler(this.button_bad_Click);
            // 
            // reset
            // 
            this.reset.Location = new System.Drawing.Point(846, 488);
            this.reset.Name = "reset";
            this.reset.Size = new System.Drawing.Size(75, 23);
            this.reset.TabIndex = 6;
            this.reset.Text = "초기화";
            this.reset.UseVisualStyleBackColor = true;
            this.reset.Click += new System.EventHandler(this.reset_Click);
            // 
            // csv
            // 
            this.csv.Location = new System.Drawing.Point(678, 104);
            this.csv.Name = "csv";
            this.csv.Size = new System.Drawing.Size(84, 23);
            this.csv.TabIndex = 7;
            this.csv.Text = "csv불러오기";
            this.csv.UseVisualStyleBackColor = true;
            this.csv.Click += new System.EventHandler(this.csv_Click);
            // 
            // modify
            // 
            this.modify.Location = new System.Drawing.Point(678, 165);
            this.modify.Name = "modify";
            this.modify.Size = new System.Drawing.Size(75, 23);
            this.modify.TabIndex = 8;
            this.modify.Text = "수정";
            this.modify.UseVisualStyleBackColor = true;
            this.modify.Click += new System.EventHandler(this.modify_Click);
            // 
            // csv_up
            // 
            this.csv_up.Location = new System.Drawing.Point(768, 104);
            this.csv_up.Name = "csv_up";
            this.csv_up.Size = new System.Drawing.Size(75, 23);
            this.csv_up.TabIndex = 9;
            this.csv_up.Text = "csv업로드";
            this.csv_up.UseVisualStyleBackColor = true;
            this.csv_up.Click += new System.EventHandler(this.csv_up_Click);
            // 
            // insert
            // 
            this.insert.Location = new System.Drawing.Point(678, 133);
            this.insert.Name = "insert";
            this.insert.Size = new System.Drawing.Size(75, 23);
            this.insert.TabIndex = 10;
            this.insert.Text = "추가";
            this.insert.UseVisualStyleBackColor = true;
            this.insert.Click += new System.EventHandler(this.insert_Click);
            // 
            // delete
            // 
            this.delete.Location = new System.Drawing.Point(678, 194);
            this.delete.Name = "delete";
            this.delete.Size = new System.Drawing.Size(75, 23);
            this.delete.TabIndex = 11;
            this.delete.Text = "삭제";
            this.delete.UseVisualStyleBackColor = true;
            this.delete.Click += new System.EventHandler(this.delete_Click);
            // 
            // button_Month
            // 
            this.button_Month.Location = new System.Drawing.Point(471, 49);
            this.button_Month.Name = "button_Month";
            this.button_Month.Size = new System.Drawing.Size(85, 23);
            this.button_Month.TabIndex = 12;
            this.button_Month.Text = "월별 불량품";
            this.button_Month.UseVisualStyleBackColor = true;
            this.button_Month.Click += new System.EventHandler(this.button_Month_Click);
            // 
            // button_hour
            // 
            this.button_hour.Location = new System.Drawing.Point(471, 20);
            this.button_hour.Name = "button_hour";
            this.button_hour.Size = new System.Drawing.Size(93, 23);
            this.button_hour.TabIndex = 13;
            this.button_hour.Text = "시간별 불량품";
            this.button_hour.UseVisualStyleBackColor = true;
            this.button_hour.Click += new System.EventHandler(this.button_hour_Click);
            // 
            // temperature
            // 
            this.temperature.Location = new System.Drawing.Point(678, 290);
            this.temperature.Name = "temperature";
            this.temperature.Size = new System.Drawing.Size(105, 23);
            this.temperature.TabIndex = 14;
            this.temperature.Text = "상태별 온도확인";
            this.temperature.UseVisualStyleBackColor = true;
            this.temperature.Click += new System.EventHandler(this.temperature_Click);
            // 
            // status
            // 
            this.status.Location = new System.Drawing.Point(678, 320);
            this.status.Name = "status";
            this.status.Size = new System.Drawing.Size(105, 23);
            this.status.TabIndex = 15;
            this.status.Text = "온도별 분포도";
            this.status.UseVisualStyleBackColor = true;
            this.status.Click += new System.EventHandler(this.status_Click);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(922, 511);
            this.Controls.Add(this.status);
            this.Controls.Add(this.temperature);
            this.Controls.Add(this.button_hour);
            this.Controls.Add(this.button_Month);
            this.Controls.Add(this.delete);
            this.Controls.Add(this.insert);
            this.Controls.Add(this.csv_up);
            this.Controls.Add(this.modify);
            this.Controls.Add(this.csv);
            this.Controls.Add(this.reset);
            this.Controls.Add(this.button_bad);
            this.Controls.Add(this.button_good);
            this.Controls.Add(this.AllPrint);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.MonthPrint);
            this.Controls.Add(this.chart1);
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "메인 화면";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button MonthPrint;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Button AllPrint;
        private System.Windows.Forms.Button button_good;
        private System.Windows.Forms.Button button_bad;
        private System.Windows.Forms.Button reset;
        private System.Windows.Forms.Button csv;
        private System.Windows.Forms.Button modify;
        private System.Windows.Forms.Button csv_up;
        private System.Windows.Forms.Button insert;
        private System.Windows.Forms.Button delete;
        private System.Windows.Forms.Button button_Month;
        private System.Windows.Forms.Button button_hour;
        private System.Windows.Forms.Button temperature;
        private System.Windows.Forms.Button status;
    }
}

