namespace HARMOLOID_Csharp
{
    partial class NoticeDialog
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
            this.textBox_Notice = new System.Windows.Forms.TextBox();
            this.button_Confirm = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox_Notice
            // 
            this.textBox_Notice.BackColor = System.Drawing.SystemColors.Control;
            this.textBox_Notice.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox_Notice.Location = new System.Drawing.Point(53, 39);
            this.textBox_Notice.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox_Notice.Multiline = true;
            this.textBox_Notice.Name = "textBox_Notice";
            this.textBox_Notice.ReadOnly = true;
            this.textBox_Notice.Size = new System.Drawing.Size(461, 25);
            this.textBox_Notice.TabIndex = 0;
            this.textBox_Notice.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // button_Confirm
            // 
            this.button_Confirm.Location = new System.Drawing.Point(239, 90);
            this.button_Confirm.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button_Confirm.Name = "button_Confirm";
            this.button_Confirm.Size = new System.Drawing.Size(93, 37);
            this.button_Confirm.TabIndex = 1;
            this.button_Confirm.Text = "确定";
            this.button_Confirm.UseVisualStyleBackColor = true;
            this.button_Confirm.Click += new System.EventHandler(this.button_Confirm_Click);
            // 
            // NoticeDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(572, 143);
            this.Controls.Add(this.button_Confirm);
            this.Controls.Add(this.textBox_Notice);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "NoticeDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "提示";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.NoticeDialog_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_Notice;
        private System.Windows.Forms.Button button_Confirm;
    }
}