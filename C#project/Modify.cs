using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace pasteurizer
{
    public partial class Modify : Form
    {
        private string[] originalCellValues; // 원본 데이터
        public event Action<string[]> DataUpdated; // 데이터 업데이트 이벤트

        public Modify(string[] cellValues)
        {
            InitializeComponent();
            // TextBox에 선택한 셀의 데이터 출력
            if (cellValues.Length >= 6)
            {
                originalCellValues = cellValues.Clone() as string[]; // 원본 데이터 복사
                textBox1.Text = cellValues[0];
                textBox2.Text = cellValues[1];
                textBox3.Text = cellValues[2];
                textBox4.Text = cellValues[3];
                textBox5.Text = cellValues[4];
                comboBox1.Text = cellValues[5]; // 추가된 텍스트박스에 데이터 설정

                textBox1.ReadOnly = true; // 첫 번째 텍스트박스를 읽기 전용으로 설정
            }

            modsave.Click += modsave_Click;
        }

        private void modsave_Click(object sender, EventArgs e)
        {
            // 입력 데이터 검증
            if (ValidateInputs())
            {
                // 수정된 데이터를 배열에 저장
                string[] updatedValues = new string[6];
                updatedValues[0] = textBox1.Text;
                updatedValues[1] = textBox2.Text;
                updatedValues[2] = textBox3.Text;
                updatedValues[3] = textBox4.Text;
                updatedValues[4] = textBox5.Text;
                updatedValues[5] = comboBox1.Text;

                // 데이터 업데이트 이벤트 호출
                DataUpdated?.Invoke(updatedValues);

                // 데이터베이스 업데이트
                DBHelper.UpdatePasteurizerData(updatedValues);

                // 폼 닫기
                this.Close();
            }
            else
            {
                MessageBox.Show("모든 필드를 올바르게 입력하세요.", "입력 오류", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private bool ValidateInputs()
        {
            // 각 텍스트 박스의 데이터가 유효한지 확인하는 로직 추가
            // 예: 필수 입력, 숫자 형식 확인 등
            return !string.IsNullOrWhiteSpace(textBox1.Text) &&
                   !string.IsNullOrWhiteSpace(textBox2.Text) &&
                   !string.IsNullOrWhiteSpace(textBox3.Text) &&
                   !string.IsNullOrWhiteSpace(textBox4.Text) &&
                   !string.IsNullOrWhiteSpace(textBox5.Text);
        }
    }
}