namespace HARMOLOID_Csharp
{
    partial class Harmonization
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Harmonization));
            this.label1 = new System.Windows.Forms.Label();
            this.label_HarmonizingTrack = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label_Tonality = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.checkedListBox_HarmonyOptions = new System.Windows.Forms.CheckedListBox();
            this.button_SaveHarmony = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(35, 51);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "调性：";
            // 
            // label_HarmonizingTrack
            // 
            this.label_HarmonizingTrack.AutoSize = true;
            this.label_HarmonizingTrack.Location = new System.Drawing.Point(113, 22);
            this.label_HarmonizingTrack.Name = "label_HarmonizingTrack";
            this.label_HarmonizingTrack.Size = new System.Drawing.Size(54, 20);
            this.label_HarmonizingTrack.TabIndex = 3;
            this.label_HarmonizingTrack.Text = "音轨名";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(35, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(84, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "当前音轨：";
            // 
            // label_Tonality
            // 
            this.label_Tonality.AutoSize = true;
            this.label_Tonality.Location = new System.Drawing.Point(86, 51);
            this.label_Tonality.Name = "label_Tonality";
            this.label_Tonality.Size = new System.Drawing.Size(39, 20);
            this.label_Tonality.TabIndex = 4;
            this.label_Tonality.Text = "调性";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(35, 83);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 20);
            this.label3.TabIndex = 5;
            this.label3.Text = "和声种类：";
            // 
            // checkedListBox_HarmonyOptions
            // 
            this.checkedListBox_HarmonyOptions.BackColor = System.Drawing.SystemColors.Control;
            this.checkedListBox_HarmonyOptions.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.checkedListBox_HarmonyOptions.CheckOnClick = true;
            this.checkedListBox_HarmonyOptions.FormattingEnabled = true;
            this.checkedListBox_HarmonyOptions.Items.AddRange(new object[] {
            "零度和声",
            "上三度和声",
            "下三度和声",
            "上六度和声",
            "下六度和声",
            "上八度和声",
            "下八度和声"});
            this.checkedListBox_HarmonyOptions.Location = new System.Drawing.Point(39, 117);
            this.checkedListBox_HarmonyOptions.Name = "checkedListBox_HarmonyOptions";
            this.checkedListBox_HarmonyOptions.Size = new System.Drawing.Size(247, 176);
            this.checkedListBox_HarmonyOptions.TabIndex = 6;
            // 
            // button_SaveHarmony
            // 
            this.button_SaveHarmony.Location = new System.Drawing.Point(90, 289);
            this.button_SaveHarmony.Name = "button_SaveHarmony";
            this.button_SaveHarmony.Size = new System.Drawing.Size(166, 45);
            this.button_SaveHarmony.TabIndex = 7;
            this.button_SaveHarmony.Text = "确定";
            this.button_SaveHarmony.UseVisualStyleBackColor = true;
            this.button_SaveHarmony.Click += new System.EventHandler(this.button_SaveHarmony_Click);
            // 
            // Harmonization
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(342, 356);
            this.Controls.Add(this.button_SaveHarmony);
            this.Controls.Add(this.checkedListBox_HarmonyOptions);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label_Tonality);
            this.Controls.Add(this.label_HarmonizingTrack);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Harmonization";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "和声生成";
            this.Load += new System.EventHandler(this.Harmonization_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label_HarmonizingTrack;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label_Tonality;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckedListBox checkedListBox_HarmonyOptions;
        private System.Windows.Forms.Button button_SaveHarmony;
    }
}