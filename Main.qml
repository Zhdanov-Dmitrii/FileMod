import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: mainWindow
    width: 300
    height: 360
    visible: true
    title: qsTr("FileMod")

    ButtonGroup { id: g1 }
    ButtonGroup { id: g2 }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        RowLayout {
            spacing: 5
            Text {
                text:"Путь к файлу"
            }

            TextField {
                id: inputFilePath
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: 5
            Text {
                text:"Маска"
            }

            TextField {
                id: mask
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: 5
            CheckBox {id: deleteFile}
            Text {text: " Удалять входной файл"}
        }

        RowLayout {
            spacing: 5
            Text {
                text:"Папка для сохранения"
            }
            TextField {
                id: outputFilePath
                Layout.fillWidth: true
            }
        }

        RowLayout {Text{text:"При повторении"}}

        RowLayout {
            RadioButton {
                checked: true
                text: "Перезаписать"
                ButtonGroup.group: g1
            }
        }

        RowLayout {
            RadioButton {
                checked: true
                text: "Модифицировать"
                ButtonGroup.group: g1
            }
        }

        RowLayout {
            RadioButton {
                checked: true
                text: "Сделать счетчик"
                ButtonGroup.group: g1
            }
        }

        RowLayout { Text { text: "Режим запуска" } }

        RowLayout {
            spacing: 5
            RadioButton {
                id: timerRB
                checked: true
                text: "По таймеру"
                ButtonGroup.group: g2
            }
            SpinBox {
                id: interval
                editable: true
                from: 1
                visible: timerRB.checked
            }
            Text{
                visible: timerRB.checked
                text: "сек"
            }
        }

        RowLayout {
            RadioButton {
                checked: true
                text: "Один запуск"
                ButtonGroup.group: g2
            }
        }

        RowLayout {
            spacing: 5
            Text{ text:"XOR" }
            SpinBox {
                id: xorByte
                editable: true
                from: 0
                to: 255
                stepSize: 1
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: 5
            Button {
                id: startButton
                text: "старт"
                Layout.fillWidth: true
                onClicked: {
                    if (g2.checkedButton == timerRB) {
                        stopButton.visible = true
                        enabled: false
                    }

                    controller.run(inputFilePath.text, outputFilePath.text, mask.text,
                                   deleteFile.checked, g1.checkedButton.text,
                                   g2.checkedButton.text, interval.value, xorByte.value)
                }
            }

            Button {
                id: stopButton
                text: "стоп"
                visible: false
                Layout.fillWidth: true
                onClicked: {
                    controller.stopTimer()
                    startButton.enabled = true
                    visible = false
                }
            }
        }
    }
}
