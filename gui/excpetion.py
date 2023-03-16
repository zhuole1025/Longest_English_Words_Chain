# -*- codeing = utf-8 -*-
# @Time : 2023/3/16 8:07
# @Author : llcc
# @File : excpetion.py
# @Software : PyCharm
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel, QMessageBox
import sys

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.button = QPushButton('Raise Exception', self)
        self.button.clicked.connect(self.on_button_click)
        self.setCentralWidget(self.button)

        self.error_label = QLabel('', self)
        self.error_label.setStyleSheet('color: red')
        self.error_label.move(50, 50)
        self.error_label.hide()

    def on_button_click(self):
        try:
            # raise an exception here
            1 / 0
        except Exception as e:
            error_msg = str(e)
            # show error message in a message box
            # QMessageBox.critical(self, 'Error', error_msg)
            # show error message in a label
            self.error_label.setText(error_msg)
            self.error_label.show()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
