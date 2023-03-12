import os
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QTextEdit, QPushButton, QHBoxLayout, QVBoxLayout, \
    QFileDialog, QRadioButton, QButtonGroup, QCheckBox


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        # 创建界面元素
        self.file_path_label = QLabel("File Path:")
        self.file_path_edit = QLineEdit()
        self.browse_button = QPushButton("Browse")
        self.browse_button.clicked.connect(self.open_file_dialog)

        self.text_edit = QTextEdit()

        self.output_text = QTextEdit()
        self.output_text.setReadOnly(True)
        self.export_button = QPushButton("Export")
        self.export_button.clicked.connect(self.on_export_btn_click)

        self.submit_button = QPushButton("Submit")
        self.submit_button.clicked.connect(self.submit_button_click)

        # 添加功能型参数按钮
        self.radio_btn_n = QRadioButton('ALL')
        self.radio_btn_w = QRadioButton('WORD')
        self.radio_btn_c = QRadioButton('CHAR')

        # 添加附加型参数按钮
        self.radio_btn_h = QCheckBox('h', self)
        self.radio_btn_t = QCheckBox('t', self)
        self.radio_btn_j = QCheckBox('j', self)
        self.radio_btn_r = QCheckBox('r', self)

        self.line_input_h = QLineEdit(self)
        self.line_input_t = QLineEdit(self)
        self.line_input_j = QLineEdit(self)

        # 水平布局
        file_layout = QHBoxLayout()
        file_layout.addWidget(self.file_path_label)
        file_layout.addWidget(self.file_path_edit)
        file_layout.addWidget(self.browse_button)
        file_layout.addWidget(self.submit_button)

        ## 功能型参数
        funcBtn_layout = QHBoxLayout()
        button_group = QButtonGroup()
        button_group.addButton(self.radio_btn_n)
        button_group.addButton(self.radio_btn_w)
        button_group.addButton(self.radio_btn_c)
        funcBtn_layout.addWidget(QLabel('Select Region:', self))
        funcBtn_layout.addWidget(self.radio_btn_n)
        funcBtn_layout.addWidget(self.radio_btn_w)
        funcBtn_layout.addWidget(self.radio_btn_c)

        ## 附加型参数
        func_h_layout = QHBoxLayout()
        func_h_layout.addWidget(self.radio_btn_h)
        func_h_layout.addWidget(self.line_input_h)

        func_t_layout = QHBoxLayout()
        func_t_layout.addWidget(self.radio_btn_t)
        func_t_layout.addWidget(self.line_input_t)

        func_j_layout = QHBoxLayout()
        func_j_layout.addWidget(self.radio_btn_j)
        func_j_layout.addWidget(self.line_input_j)

        # 垂直布局
        vbox = QVBoxLayout()
        vbox.addLayout(file_layout)

        vbox.addLayout(funcBtn_layout)

        vbox.addLayout(func_h_layout)
        vbox.addLayout(func_t_layout)
        vbox.addLayout(func_j_layout)
        vbox.addWidget(self.radio_btn_r)

        vbox.addWidget(self.text_edit)
        vbox.addWidget(self.output_text)
        vbox.addWidget(self.export_button)
        self.export_button.hide()
        self.output_text.hide()
        # vbox.addWidget(self.submit_button)

        # button actions
        # self.line_input_h.hide()
        # self.line_input_t.hide()
        # self.line_input_j.hide()
        # self.radio_button_h.stateChanged.connect(self.on_radio_button_h_changed)
        self.radio_btn_h.stateChanged.connect(self.on_radio_btn_h_changed)
        self.radio_btn_t.stateChanged.connect(self.on_radio_btn_t_changed)
        self.radio_btn_j.stateChanged.connect(self.on_radio_btn_j_changed)
        self.radio_btn_r.stateChanged.connect(self.on_radio_btn_r_changed)

        # 设置主窗口布局
        self.setLayout(vbox)

        # 设置主窗口属性
        self.setGeometry(100, 100, 500, 400)
        self.setWindowTitle('Text Input Example')
        self.show()

    def open_file_dialog(self):
        # 浏览本地文件
        options = QFileDialog.Options()
        options |= QFileDialog.DontUseNativeDialog
        file_name, _ = QFileDialog.getOpenFileName(self, "Open File", "", "Text Files (*.txt)", options=options)
        if file_name:
            with open(file_name, 'r') as file:
                self.text_edit.setText(file.read())
                self.file_path_edit.setText(file_name)

    def on_export_btn_click(self):
        filename, _ = QFileDialog.getSaveFileName(self, 'Save File', os.path.expanduser("~/Desktop"),
                                                  "Text Files (*.txt)")

        if filename:
            with open(filename, 'w') as f:
                f.write(self.output_text.toPlainText())

    def on_radio_btn_h_changed(self, state):
        if state == 2:
            self.line_input_h.show()
        else:
            self.line_input_h.hide()

    def on_radio_btn_t_changed(self, state):
        if state == 2:
            self.line_input_h.show()
        else:
            self.line_input_h.hide()

    def on_radio_btn_j_changed(self, state):
        if state == 2:
            self.line_input_h.show()
        else:
            self.line_input_h.hide()

    def on_radio_btn_r_changed(self, state):
        if state == 2:
            self.line_input_h.show()
        else:
            self.line_input_h.hide()

    def submit_button_click(self):
        text = self.text_edit.toPlainText()
        print("text: ", text)
        print("h: ", self.line_input_h.text())
        # self.text_edit.hide()
        self.output_text.show()
        self.export_button.show()
        if self.radio_btn_n.isChecked():
            print('您选择了 n')
        elif self.radio_btn_w.isChecked():
            print('您选择了 w')

        self.output_text.append("需要输出的内容")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_window = MainWindow()
    sys.exit(app.exec_())

