namespace HARMOLOID_Csharp
{
    partial class HARMOLOID
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(HARMOLOID));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.载入ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存为ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.用户手册ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获得更新ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BUG提交ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于HARMOLOIDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_FileInfo = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox_TrackInfo = new System.Windows.Forms.TextBox();
            this.listBox_TrackList = new System.Windows.Forms.ListBox();
            this.button_调性标记 = new System.Windows.Forms.Button();
            this.button_和声生成 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.logo = new System.Windows.Forms.PictureBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.logo)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件ToolStripMenuItem,
            this.帮助ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(7, 3, 0, 3);
            this.menuStrip1.Size = new System.Drawing.Size(828, 30);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件ToolStripMenuItem
            // 
            this.文件ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.载入ToolStripMenuItem,
            this.保存ToolStripMenuItem,
            this.另存为ToolStripMenuItem});
            this.文件ToolStripMenuItem.Name = "文件ToolStripMenuItem";
            this.文件ToolStripMenuItem.Size = new System.Drawing.Size(51, 24);
            this.文件ToolStripMenuItem.Text = "文件";
            // 
            // 载入ToolStripMenuItem
            // 
            this.载入ToolStripMenuItem.Name = "载入ToolStripMenuItem";
            this.载入ToolStripMenuItem.Size = new System.Drawing.Size(123, 24);
            this.载入ToolStripMenuItem.Text = "载入";
            this.载入ToolStripMenuItem.Click += new System.EventHandler(this.载入ToolStripMenuItem_Click);
            // 
            // 保存ToolStripMenuItem
            // 
            this.保存ToolStripMenuItem.Enabled = false;
            this.保存ToolStripMenuItem.Name = "保存ToolStripMenuItem";
            this.保存ToolStripMenuItem.Size = new System.Drawing.Size(123, 24);
            this.保存ToolStripMenuItem.Text = "保存";
            this.保存ToolStripMenuItem.Click += new System.EventHandler(this.保存ToolStripMenuItem_Click);
            // 
            // 另存为ToolStripMenuItem
            // 
            this.另存为ToolStripMenuItem.Enabled = false;
            this.另存为ToolStripMenuItem.Name = "另存为ToolStripMenuItem";
            this.另存为ToolStripMenuItem.Size = new System.Drawing.Size(123, 24);
            this.另存为ToolStripMenuItem.Text = "另存为";
            this.另存为ToolStripMenuItem.Click += new System.EventHandler(this.另存为ToolStripMenuItem_Click);
            // 
            // 帮助ToolStripMenuItem
            // 
            this.帮助ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.用户手册ToolStripMenuItem,
            this.获得更新ToolStripMenuItem,
            this.BUG提交ToolStripMenuItem,
            this.关于HARMOLOIDToolStripMenuItem});
            this.帮助ToolStripMenuItem.Name = "帮助ToolStripMenuItem";
            this.帮助ToolStripMenuItem.Size = new System.Drawing.Size(51, 24);
            this.帮助ToolStripMenuItem.Text = "帮助";
            // 
            // 用户手册ToolStripMenuItem
            // 
            this.用户手册ToolStripMenuItem.Name = "用户手册ToolStripMenuItem";
            this.用户手册ToolStripMenuItem.Size = new System.Drawing.Size(203, 24);
            this.用户手册ToolStripMenuItem.Text = "用户手册";
            this.用户手册ToolStripMenuItem.Click += new System.EventHandler(this.用户手册ToolStripMenuItem_Click);
            // 
            // 获得更新ToolStripMenuItem
            // 
            this.获得更新ToolStripMenuItem.Name = "获得更新ToolStripMenuItem";
            this.获得更新ToolStripMenuItem.Size = new System.Drawing.Size(203, 24);
            this.获得更新ToolStripMenuItem.Text = "获得更新";
            this.获得更新ToolStripMenuItem.Click += new System.EventHandler(this.获得更新ToolStripMenuItem_Click);
            // 
            // BUG提交ToolStripMenuItem
            // 
            this.BUG提交ToolStripMenuItem.Name = "BUG提交ToolStripMenuItem";
            this.BUG提交ToolStripMenuItem.Size = new System.Drawing.Size(203, 24);
            this.BUG提交ToolStripMenuItem.Text = "BUG提交";
            this.BUG提交ToolStripMenuItem.Click += new System.EventHandler(this.BUG提交ToolStripMenuItem_Click);
            // 
            // 关于HARMOLOIDToolStripMenuItem
            // 
            this.关于HARMOLOIDToolStripMenuItem.Name = "关于HARMOLOIDToolStripMenuItem";
            this.关于HARMOLOIDToolStripMenuItem.Size = new System.Drawing.Size(203, 24);
            this.关于HARMOLOIDToolStripMenuItem.Text = "关于HARMOLOID";
            this.关于HARMOLOIDToolStripMenuItem.Click += new System.EventHandler(this.关于HARMOLOIDToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(317, 59);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(69, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "文件信息";
            // 
            // textBox_FileInfo
            // 
            this.textBox_FileInfo.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox_FileInfo.Location = new System.Drawing.Point(320, 97);
            this.textBox_FileInfo.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox_FileInfo.Multiline = true;
            this.textBox_FileInfo.Name = "textBox_FileInfo";
            this.textBox_FileInfo.ReadOnly = true;
            this.textBox_FileInfo.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_FileInfo.Size = new System.Drawing.Size(473, 92);
            this.textBox_FileInfo.TabIndex = 4;
            this.textBox_FileInfo.Text = "文件未载入。";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(25, 169);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 20);
            this.label2.TabIndex = 5;
            this.label2.Text = "选择音轨";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(317, 212);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(69, 20);
            this.label3.TabIndex = 6;
            this.label3.Text = "音轨信息";
            // 
            // textBox_TrackInfo
            // 
            this.textBox_TrackInfo.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox_TrackInfo.Location = new System.Drawing.Point(320, 248);
            this.textBox_TrackInfo.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox_TrackInfo.Multiline = true;
            this.textBox_TrackInfo.Name = "textBox_TrackInfo";
            this.textBox_TrackInfo.ReadOnly = true;
            this.textBox_TrackInfo.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_TrackInfo.Size = new System.Drawing.Size(473, 143);
            this.textBox_TrackInfo.TabIndex = 7;
            this.textBox_TrackInfo.Text = "请选择音轨。";
            // 
            // listBox_TrackList
            // 
            this.listBox_TrackList.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listBox_TrackList.FormattingEnabled = true;
            this.listBox_TrackList.ItemHeight = 20;
            this.listBox_TrackList.Items.AddRange(new object[] {
            "文件未载入。"});
            this.listBox_TrackList.Location = new System.Drawing.Point(29, 208);
            this.listBox_TrackList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.listBox_TrackList.Name = "listBox_TrackList";
            this.listBox_TrackList.Size = new System.Drawing.Size(256, 244);
            this.listBox_TrackList.TabIndex = 8;
            this.listBox_TrackList.SelectedIndexChanged += new System.EventHandler(this.listBox_TrackList_SelectedIndexChanged);
            // 
            // button_调性标记
            // 
            this.button_调性标记.Enabled = false;
            this.button_调性标记.Location = new System.Drawing.Point(321, 410);
            this.button_调性标记.Name = "button_调性标记";
            this.button_调性标记.Size = new System.Drawing.Size(227, 37);
            this.button_调性标记.TabIndex = 9;
            this.button_调性标记.Text = "调性标记";
            this.button_调性标记.UseVisualStyleBackColor = true;
            this.button_调性标记.Click += new System.EventHandler(this.button_标记调性_Click);
            // 
            // button_和声生成
            // 
            this.button_和声生成.Enabled = false;
            this.button_和声生成.Location = new System.Drawing.Point(567, 410);
            this.button_和声生成.Name = "button_和声生成";
            this.button_和声生成.Size = new System.Drawing.Size(226, 37);
            this.button_和声生成.TabIndex = 10;
            this.button_和声生成.Text = "和声生成";
            this.button_和声生成.UseVisualStyleBackColor = true;
            this.button_和声生成.Click += new System.EventHandler(this.button_和声生成_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(28, 121);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(259, 20);
            this.label4.TabIndex = 12;
            this.label4.Text = "ver 1.1          科林/sdercolin © 2015";
            // 
            // logo
            // 
            this.logo.Image = global::HARMOLOID_Csharp.Properties.Resources.HARMOLOID;
            this.logo.Location = new System.Drawing.Point(29, 53);
            this.logo.Name = "logo";
            this.logo.Size = new System.Drawing.Size(256, 62);
            this.logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.logo.TabIndex = 11;
            this.logo.TabStop = false;
            // 
            // HARMOLOID
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(828, 472);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.logo);
            this.Controls.Add(this.button_和声生成);
            this.Controls.Add(this.button_调性标记);
            this.Controls.Add(this.listBox_TrackList);
            this.Controls.Add(this.textBox_TrackInfo);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox_FileInfo);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.Name = "HARMOLOID";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "HARMOLOID 1.1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.HARMOLOID_FormClosing);
            this.Load += new System.EventHandler(this.c_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.logo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 文件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 帮助ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 载入ToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_FileInfo;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox_TrackInfo;
        private System.Windows.Forms.ListBox listBox_TrackList;
        private System.Windows.Forms.Button button_调性标记;
        private System.Windows.Forms.Button button_和声生成;
        private System.Windows.Forms.ToolStripMenuItem 另存为ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存ToolStripMenuItem;
        private System.Windows.Forms.PictureBox logo;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ToolStripMenuItem 关于HARMOLOIDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 用户手册ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获得更新ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BUG提交ToolStripMenuItem;
    }
}

