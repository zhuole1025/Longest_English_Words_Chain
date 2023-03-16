import os
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QTextEdit, QPushButton, QHBoxLayout, QVBoxLayout, \
    QFileDialog, QRadioButton, QButtonGroup, QCheckBox
import ctypes


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.option = {'h': 0, 't': 0, 'j': 0, 'r': 0}
        # elements

        ## file input and output
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

        ## arg option n,w,c
        self.radio_btn_n = QRadioButton('ALL')
        self.radio_btn_w = QRadioButton('WORD')
        self.radio_btn_c = QRadioButton('CHAR')

        ## arg option h,t,j,r
        self.radio_btn_h = QCheckBox('h', self)
        self.radio_btn_t = QCheckBox('t', self)
        self.radio_btn_j = QCheckBox('j', self)
        self.radio_btn_r = QCheckBox('r', self)
        ### input char
        self.line_input_h = QLineEdit(self)
        self.line_input_t = QLineEdit(self)
        self.line_input_j = QLineEdit(self)

        # horizontal layout
        file_layout = QHBoxLayout()
        file_layout.addWidget(self.file_path_label)
        file_layout.addWidget(self.file_path_edit)
        file_layout.addWidget(self.browse_button)
        file_layout.addWidget(self.submit_button)

        ## main arg
        funcBtn_layout = QHBoxLayout()
        button_group = QButtonGroup()
        button_group.addButton(self.radio_btn_n)
        button_group.addButton(self.radio_btn_w)
        button_group.addButton(self.radio_btn_c)
        funcBtn_layout.addWidget(QLabel('Select Region:', self))
        funcBtn_layout.addWidget(self.radio_btn_n)
        funcBtn_layout.addWidget(self.radio_btn_w)
        funcBtn_layout.addWidget(self.radio_btn_c)

        ## attach arg
        func_h_layout = QHBoxLayout()
        func_h_layout.addWidget(self.radio_btn_h)
        func_h_layout.addWidget(self.line_input_h)

        func_t_layout = QHBoxLayout()
        func_t_layout.addWidget(self.radio_btn_t)
        func_t_layout.addWidget(self.line_input_t)

        func_j_layout = QHBoxLayout()
        func_j_layout.addWidget(self.radio_btn_j)
        func_j_layout.addWidget(self.line_input_j)

        # vertical layout
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

        # button actions
        # self.line_input_h.hide()
        # self.line_input_t.hide()
        # self.line_input_j.hide()
        # self.radio_button_h.stateChanged.connect(self.on_radio_button_h_changed)
        self.radio_btn_h.stateChanged.connect(self.on_radio_btn_h_changed)
        self.radio_btn_t.stateChanged.connect(self.on_radio_btn_t_changed)
        self.radio_btn_j.stateChanged.connect(self.on_radio_btn_j_changed)
        self.radio_btn_r.stateChanged.connect(self.on_radio_btn_r_changed)

        # set main window's layout
        self.setLayout(vbox)

        # set main window's attributes
        self.setGeometry(100, 100, 500, 400)
        self.setWindowTitle('Find word chain!')
        self.show()

    # browse local files and dirs
    def open_file_dialog(self):
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
            self.option['h'] = 1
            self.line_input_h.show()
        else:
            self.option['h'] = 0
            self.line_input_h.hide()

    def on_radio_btn_t_changed(self, state):
        if state == 2:
            self.option['t'] = 1
            self.line_input_t.show()
        else:
            self.option['t'] = 0
            self.line_input_t.hide()

    def on_radio_btn_j_changed(self, state):
        if state == 2:
            self.option['j'] = 1
            self.line_input_j.show()
        else:
            self.option['t'] = 0
            self.line_input_j.hide()

    def on_radio_btn_r_changed(self, state):
        if state == 2:
            self.option['r'] = 1
        else:
            self.option['r'] = 0

    def error_handler(self, exception_type, exception_value):
        print(f"Exception: {exception_value}")
        ctypes.pythonapi.PyErr_SetString(exception_type, str(exception_value).encode("utf-8"))

    def extract_words(self, text):
        words = []
        length = len(text)
        i = 0
        while i < length:
            j = i
            while i < length and text[i].isalpha():
                i = i + 1
            if j != i:
                words.append(text[j:i])
            i = i + 1
        for i in range(len(words)):
            print(words[i])
        return words, len(words)

    def submit_button_click(self):
        C_FUNC_TYPE = ctypes.CFUNCTYPE(None, ctypes.py_object, ctypes.py_object)
        c_func = C_FUNC_TYPE(self.error_handler)

        num_rows = 20000
        num_cols = 200
        my_dll = ctypes.CDLL("./bin/core.dll")
        my_dll.gen_chains_all.argtypes = [ctypes.POINTER(ctypes.c_char_p),
                                          ctypes.c_int, ctypes.POINTER(ctypes.c_char_p)]
        my_dll.gen_chains_all.errcheck = c_func

        text = self.text_edit.toPlainText()

        words, size = self.extract_words(text)
        # switch words to c_type
        c_words = [ctypes.c_char_p(w.encode()) for w in words]
        # c_arr = (ctypes.c_char_p * len(words))(*c_words)
        c_arr = ctypes.POINTER(ctypes.c_char_p)(*c_words)
        print(type(c_arr))
        c_len = ctypes.c_int(size)
        result = ctypes.POINTER(ctypes.c_char_p)()
        # result = (ctypes.c_char_p * num_rows)()
        # for i in range(num_rows):
        #     result[i] = ctypes.c_char_p()
        print(type(result))
        # print(type(result[0]))

        ans = -1
        try:
            ans = my_dll.gen_chains_all(c_arr, size, result)
        except Exception as e:
            print(f"Error: {e}")
        print(ans)
        for i in range(ans):
            print(result[i].decode('utf-8'))
        # print("text: ", text)
        # print("h: ", self.line_input_h.text())
        # self.text_edit.hide()
        self.output_text.show()
        self.export_button.show()
        if self.radio_btn_n.isChecked():
            print('')
        elif self.radio_btn_w.isChecked():
            print('')
        del my_dll
        self.output_text.clear()
        self.output_text.append("contents")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_window = MainWindow()
    sys.exit(app.exec_())
