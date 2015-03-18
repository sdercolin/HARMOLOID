namespace HARMOLOID_Csharp
{
    partial class USTSaving
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(USTSaving));
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox_HarmoToSave = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Confirm = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(49, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(174, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "选择您要保存的和声轨：";
            // 
            // comboBox_HarmoToSave
            // 
            this.comboBox_HarmoToSave.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_HarmoToSave.FormattingEnabled = true;
            this.comboBox_HarmoToSave.Location = new System.Drawing.Point(53, 53);
            this.comboBox_HarmoToSave.Name = "comboBox_HarmoToSave";
            this.comboBox_HarmoToSave.Size = new System.Drawing.Size(334, 28);
            this.comboBox_HarmoToSave.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(49, 91);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(338, 48);
            this.label1.TabIndex = 5;
            this.label1.Text = "若选择“全部保存”，则全部和声轨都将以默认文件名格式保存到原文件的目录下。\r\n";
            // 
            // Confirm
            // 
            this.Confirm.Location = new System.Drawing.Point(157, 142);
            this.Confirm.Name = "Confirm";
            this.Confirm.Size = new System.Drawing.Size(107, 37);
            this.Confirm.TabIndex = 6;
            this.Confirm.Text = "确认";
            this.Confirm.UseVisualStyleBackColor = true;
            this.Confirm.Click += new System.EventHandler(this.Confirm_Click);
            // 
            // Cancel
            // 
            this.Cancel.Location = new System.Drawing.Point(280, 142);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(107, 37);
            this.Cancel.TabIndex = 7;
            this.Cancel.Text = "取消";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // USTSaving
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(448, 202);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.Confirm);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBox_HarmoToSave);
            this.Controls.Add(this.label2);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "USTSaving";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "保存为UST";
            this.Load += new System.EventHandler(this.USTSaving_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox_HarmoToSave;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Confirm;
        private System.Windows.Forms.Button Cancel;
    }
}