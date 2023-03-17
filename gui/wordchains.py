import os
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QTextEdit, QPushButton, QHBoxLayout, QVBoxLayout, \
    QFileDialog, QRadioButton, QButtonGroup, QCheckBox
from ctypes import *

# C_FUNC_TYPE = CFUNCTYPE(None, py_object, py_object)
# c_func = C_FUNC_TYPE(error_handler)
num_rows = 20005
num_cols = 200


def extract_words(text):
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


def error_handler(exception_type, exception_value, traceback):
    print(f"Exception: {exception_value}")
    print(traceback)
    pythonapi.PyErr_SetString(exception_type, str(exception_value).encode("utf-8"))


# switch words to c_type
def process_words(words):
    c_words = [c_char_p(w.encode()) for w in words]
    c_arr = (c_char_p * len(words))(*c_words)
    # print(type(c_arr))
    return c_arr


def gen_chains_all(words, len_):
    ans = -1
    my_dll_ = CDLL("./bin/core.dll")
    func = my_dll_.gen_chains_all
    func.argtype = [(c_char_p * num_rows)(), c_int, (c_char_p * num_rows)()]
    func.restype = c_int
    func.errcheck = error_handler

    c_arr = process_words(words)
    c_len = c_int(len_)
    result_ptr = (c_char_p * num_rows)()
    try:
        ans = func(c_arr, c_len, result_ptr)
    except Exception as e:
        print(f" myError: {e}")
    # print(ans)
    res = []
    for i in range(ans):
        print(result_ptr[i])
        # print(result_ptr[i].decode('utf-8'))
        res.append(result_ptr[i].decode('utf-8'))
    del my_dll_
    return res


def gen_chain_word_or_char(type_, words, len_, head, tail, skip, enable_loop):
    ans = -1
    my_dll_ = CDLL("./bin/core.dll")
    func = my_dll_.gen_chain_word if type_ == 'w' else my_dll_.gen_chain_char
    # func.restype = c_int
    # func.errcheck = c_func

    c_arr = process_words(words)
    c_len = c_int(len_)
    c_head = c_char(head)
    c_tail = c_char(tail)
    c_skip = c_char(skip)
    c_enable_loop = c_bool(enable_loop)
    result_ptr = (c_char_p * num_rows)()
    try:
        ans = func(c_arr, c_len, result_ptr, c_head, c_tail, c_skip, c_enable_loop)
    except Exception as e:
        print(f"Error: {e}")
    res = []
    for i in range(ans):
        print(result_ptr[i].decode('utf-8'))
        res.append(result_ptr[i].decode('utf-8'))
    del my_dll_
    return res


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

    def submit_button_click(self):
        self.output_text.clear()
        text = self.text_edit.toPlainText()
        words, size = extract_words(text)
        result = gen_chains_all(words, size)
        # print("text: ", text)
        # print("h: ", self.line_input_h.text())
        # self.text_edit.hide()
        self.output_text.show()
        self.export_button.show()
        if self.radio_btn_n.isChecked():
            print('')
        elif self.radio_btn_w.isChecked():
            print('')
        for i in range(len(result)):
            self.output_text.append(result[i])


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_window = MainWindow()
    sys.exit(app.exec_())
