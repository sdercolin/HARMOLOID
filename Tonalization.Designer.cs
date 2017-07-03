namespace HARMOLOID_Csharp
{
    partial class Tonalization
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem(new string[] {
            "0",
            "0",
            "-",
            ""}, -1);
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Tonalization));
            this.label1 = new System.Windows.Forms.Label();
            this.label_TonalizingTrack = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.listView_PassageList = new System.Windows.Forms.ListView();
            this.PassageNum = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.StartBarNum = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.EndBarNum = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Tonality = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.comboBox_PassageNum = new System.Windows.Forms.ComboBox();
            this.textBox_StartBarNum = new System.Windows.Forms.TextBox();
            this.textBox_EndBarNum = new System.Windows.Forms.TextBox();
            this.button_PassageEditConfirm = new System.Windows.Forms.Button();
            this.button_ResetTonality = new System.Windows.Forms.Button();
            this.button_AutoTonalize1 = new System.Windows.Forms.Button();
            this.button_AutoTonalize2 = new System.Windows.Forms.Button();
            this.button_SaveTonality = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.listView_BarList = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.button_TonalizaionHelp = new System.Windows.Forms.Button();
            this.comboBox_TonalityInput = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = ProgramTexts.GetProgramText("trackbeingprocessed_text");
            // 
            // label_TonalizingTrack
            // 
            this.label_TonalizingTrack.AutoSize = true;
            this.label_TonalizingTrack.Location = new System.Drawing.Point(94, 18);
            this.label_TonalizingTrack.Name = "label_TonalizingTrack";
            this.label_TonalizingTrack.Size = new System.Drawing.Size(72, 17);
            this.label_TonalizingTrack.TabIndex = 1;
            this.label_TonalizingTrack.Text = "Trackname";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = ProgramTexts.GetProgramText("passagelist_text");
            // 
            // listView_PassageList
            // 
            this.listView_PassageList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PassageNum,
            this.StartBarNum,
            this.EndBarNum,
            this.Tonality});
            this.listView_PassageList.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            listViewItem1.StateImageIndex = 0;
            this.listView_PassageList.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem1});
            this.listView_PassageList.Location = new System.Drawing.Point(28, 82);
            this.listView_PassageList.MultiSelect = false;
            this.listView_PassageList.Name = "listView_PassageList";
            this.listView_PassageList.ShowGroups = false;
            this.listView_PassageList.Size = new System.Drawing.Size(456, 97);
            this.listView_PassageList.TabIndex = 3;
            this.listView_PassageList.UseCompatibleStateImageBehavior = false;
            this.listView_PassageList.View = System.Windows.Forms.View.Details;
            // 
            // PassageNum
            // 
            this.PassageNum.Text = ProgramTexts.GetProgramText("passageno");
            this.PassageNum.Width = 86;
            // 
            // StartBarNum
            // 
            this.StartBarNum.Text = ProgramTexts.GetProgramText("barstart");
            this.StartBarNum.Width = 102;
            // 
            // EndBarNum
            // 
            this.EndBarNum.Text = ProgramTexts.GetProgramText("barend");
            this.EndBarNum.Width = 112;
            // 
            // Tonality
            // 
            this.Tonality.Text = ProgramTexts.GetProgramText("tonality");
            this.Tonality.Width = 120;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 192);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(112, 17);
            this.label3.TabIndex = 4;
            this.label3.Text = ProgramTexts.GetProgramText("passageedit_text");
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(24, 221);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(112, 17);
            this.label4.TabIndex = 5;
            this.label4.Text = ProgramTexts.GetProgramText("passageno");
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(111, 221);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(62, 17);
            this.label5.TabIndex = 6;
            this.label5.Text = ProgramTexts.GetProgramText("barstart");
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(211, 221);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 17);
            this.label6.TabIndex = 7;
            this.label6.Text = ProgramTexts.GetProgramText("barend");
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(312, 220);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 17);
            this.label7.TabIndex = 8;
            this.label7.Text = ProgramTexts.GetProgramText("tonality");
            // 
            // comboBox_PassageNum
            // 
            this.comboBox_PassageNum.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_PassageNum.FormattingEnabled = true;
            this.comboBox_PassageNum.Location = new System.Drawing.Point(28, 244);
            this.comboBox_PassageNum.Name = "comboBox_PassageNum";
            this.comboBox_PassageNum.Size = new System.Drawing.Size(65, 25);
            this.comboBox_PassageNum.TabIndex = 9;
            this.comboBox_PassageNum.SelectedIndexChanged += new System.EventHandler(this.comboBox_PassageNum_SelectedIndexChanged);
            // 
            // textBox_StartBarNum
            // 
            this.textBox_StartBarNum.Enabled = false;
            this.textBox_StartBarNum.Location = new System.Drawing.Point(115, 245);
            this.textBox_StartBarNum.Name = "textBox_StartBarNum";
            this.textBox_StartBarNum.Size = new System.Drawing.Size(80, 23);
            this.textBox_StartBarNum.TabIndex = 10;
            // 
            // textBox_EndBarNum
            // 
            this.textBox_EndBarNum.Location = new System.Drawing.Point(215, 245);
            this.textBox_EndBarNum.Name = "textBox_EndBarNum";
            this.textBox_EndBarNum.Size = new System.Drawing.Size(80, 23);
            this.textBox_EndBarNum.TabIndex = 11;
            // 
            // button_PassageEditConfirm
            // 
            this.button_PassageEditConfirm.Location = new System.Drawing.Point(427, 245);
            this.button_PassageEditConfirm.Name = "button_PassageEditConfirm";
            this.button_PassageEditConfirm.Size = new System.Drawing.Size(57, 27);
            this.button_PassageEditConfirm.TabIndex = 13;
            this.button_PassageEditConfirm.Text = ProgramTexts.GetProgramText("confirm");
            this.button_PassageEditConfirm.UseVisualStyleBackColor = true;
            this.button_PassageEditConfirm.Click += new System.EventHandler(this.button_PassageEditConfirm_Click);
            // 
            // button_ResetTonality
            // 
            this.button_ResetTonality.Location = new System.Drawing.Point(316, 296);
            this.button_ResetTonality.Name = "button_ResetTonality";
            this.button_ResetTonality.Size = new System.Drawing.Size(92, 44);
            this.button_ResetTonality.TabIndex = 16;
            this.button_ResetTonality.Text = ProgramTexts.GetProgramText("reset");
            this.button_ResetTonality.UseVisualStyleBackColor = true;
            this.button_ResetTonality.Click += new System.EventHandler(this.button_ResetTonality_Click);
            // 
            // button_AutoTonalize1
            // 
            this.button_AutoTonalize1.Location = new System.Drawing.Point(28, 296);
            this.button_AutoTonalize1.Name = "button_AutoTonalize1";
            this.button_AutoTonalize1.Size = new System.Drawing.Size(267, 44);
            this.button_AutoTonalize1.TabIndex = 17;
            this.button_AutoTonalize1.Text = ProgramTexts.GetProgramText("autotonalize1");
            this.button_AutoTonalize1.UseVisualStyleBackColor = true;
            this.button_AutoTonalize1.Click += new System.EventHandler(this.button_AutoTonalize1_Click);
            // 
            // button_AutoTonalize2
            // 
            this.button_AutoTonalize2.Location = new System.Drawing.Point(28, 348);
            this.button_AutoTonalize2.Name = "button_AutoTonalize2";
            this.button_AutoTonalize2.Size = new System.Drawing.Size(267, 44);
            this.button_AutoTonalize2.TabIndex = 18;
            this.button_AutoTonalize2.Text = ProgramTexts.GetProgramText("autotonalize2");
            this.button_AutoTonalize2.UseVisualStyleBackColor = true;
            this.button_AutoTonalize2.Click += new System.EventHandler(this.button_AutoTonalize2_Click);
            // 
            // button_SaveTonality
            // 
            this.button_SaveTonality.Location = new System.Drawing.Point(316, 348);
            this.button_SaveTonality.Name = "button_SaveTonality";
            this.button_SaveTonality.Size = new System.Drawing.Size(92, 44);
            this.button_SaveTonality.TabIndex = 19;
            this.button_SaveTonality.Text = ProgramTexts.GetProgramText("confirm");
            this.button_SaveTonality.UseVisualStyleBackColor = true;
            this.button_SaveTonality.Click += new System.EventHandler(this.button_SaveTonality_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(509, 18);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(55, 17);
            this.label8.TabIndex = 20;
            this.label8.Text = ProgramTexts.GetProgramText("barlist_text");
            // 
            // listView_BarList
            // 
            this.listView_BarList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.listView_BarList.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listView_BarList.Location = new System.Drawing.Point(513, 49);
            this.listView_BarList.MultiSelect = false;
            this.listView_BarList.Name = "listView_BarList";
            this.listView_BarList.ShowGroups = false;
            this.listView_BarList.Size = new System.Drawing.Size(501, 343);
            this.listView_BarList.TabIndex = 21;
            this.listView_BarList.UseCompatibleStateImageBehavior = false;
            this.listView_BarList.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = ProgramTexts.GetProgramText("barno");
            this.columnHeader1.Width = 65;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = ProgramTexts.GetProgramText("content");
            this.columnHeader2.Width = 421;
            // 
            // button_TonalizaionHelp
            // 
            this.button_TonalizaionHelp.Location = new System.Drawing.Point(427, 296);
            this.button_TonalizaionHelp.Name = "button_TonalizaionHelp";
            this.button_TonalizaionHelp.Size = new System.Drawing.Size(57, 96);
            this.button_TonalizaionHelp.TabIndex = 22;
            this.button_TonalizaionHelp.Text = ProgramTexts.GetProgramText("help");
            this.button_TonalizaionHelp.UseVisualStyleBackColor = true;
            this.button_TonalizaionHelp.Click += new System.EventHandler(this.button_TonalizaionHelp_Click);
            // 
            // comboBox_TonalityInput
            // 
            this.comboBox_TonalityInput.FormattingEnabled = true;
            this.comboBox_TonalityInput.Items.AddRange(new object[] {
            Constants.Tonality_Type(13),
            "C",
            "C#",
            "D",
            "Eb",
            "E",
            "F",
            "F#",
            "G",
            "G#",
            "A",
            "Bb",
            "B",
            Constants.Tonality_Type(12)});
            this.comboBox_TonalityInput.Location = new System.Drawing.Point(316, 244);
            this.comboBox_TonalityInput.Name = "comboBox_TonalityInput";
            this.comboBox_TonalityInput.Size = new System.Drawing.Size(92, 25);
            this.comboBox_TonalityInput.TabIndex = 23;
            // 
            // Tonalization
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1039, 413);
            this.Controls.Add(this.comboBox_TonalityInput);
            this.Controls.Add(this.button_TonalizaionHelp);
            this.Controls.Add(this.listView_BarList);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.button_SaveTonality);
            this.Controls.Add(this.button_AutoTonalize2);
            this.Controls.Add(this.button_AutoTonalize1);
            this.Controls.Add(this.button_ResetTonality);
            this.Controls.Add(this.button_PassageEditConfirm);
            this.Controls.Add(this.textBox_EndBarNum);
            this.Controls.Add(this.textBox_StartBarNum);
            this.Controls.Add(this.comboBox_PassageNum);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.listView_PassageList);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label_TonalizingTrack);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Tonalization";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = ProgramTexts.GetProgramText("tonalization");
            this.Load += new System.EventHandler(this.Tonalization_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label_TonalizingTrack;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListView listView_PassageList;
        private System.Windows.Forms.ColumnHeader PassageNum;
        private System.Windows.Forms.ColumnHeader StartBarNum;
        private System.Windows.Forms.ColumnHeader EndBarNum;
        private System.Windows.Forms.ColumnHeader Tonality;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox comboBox_PassageNum;
        private System.Windows.Forms.TextBox textBox_StartBarNum;
        private System.Windows.Forms.TextBox textBox_EndBarNum;
        private System.Windows.Forms.Button button_PassageEditConfirm;
        private System.Windows.Forms.Button button_ResetTonality;
        private System.Windows.Forms.Button button_AutoTonalize1;
        private System.Windows.Forms.Button button_AutoTonalize2;
        private System.Windows.Forms.Button button_SaveTonality;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ListView listView_BarList;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.Button button_TonalizaionHelp;
        private System.Windows.Forms.ComboBox comboBox_TonalityInput;
    }
}