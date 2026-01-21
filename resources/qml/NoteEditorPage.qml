import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root
    title: qsTr("Новая заметка")

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "<"
                onClicked: stackView.pop()
            }
            Label {
                text: root.title
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter
            }
            ToolButton {
                text: "Save"
                enabled: titleField.text.length > 0
                onClicked: {
                    notesModel.addNote(titleField.text, contentArea.text)
                    stackView.pop()
                }
            }
        }
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.horizontalCenter: parent.horizontalCenter

        anchors.margins: 20

        width: Math.min(parent.width - 40, 800)

        spacing: 10

        TextField {
            id: titleField
            placeholderText: qsTr("Заголовок")
            font.pixelSize: 18
            font.bold: true

            Layout.fillWidth: true
            background: null
        }

        Rectangle {
            height: 1
            color: "lightgray"
            Layout.fillWidth: true
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextArea {
                id: contentArea
                placeholderText: qsTr("Текст заметки (Markdown)...")
                font.pixelSize: 16
                wrapMode: TextEdit.Wrap
                textFormat: TextEdit.MarkdownText

                width: parent.width
            }
        }
    }
}
