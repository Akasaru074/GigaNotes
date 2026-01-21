import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    property int noteId: -1
    property string initialTitle: ""
    property string initialContent: ""

    title: noteId === -1 ? qsTr("Новая заметка") : qsTr("Редактирование")

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
                    if (root.noteId === -1) {
                        notesModel.addNote(titleField.text, contentArea.text)
                    } else {
                        notesModel.updateNote(root.noteId, titleField.text, contentArea.text)
                    }
                    stackView.pop(null)
                }
            }
        }
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        width: Math.max(0, Math.min(parent.width - 40, 800))

        anchors.margins: 20
        spacing: 10

        TextField {
            id: titleField
            text: root.initialTitle
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
            id: view
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextArea {
                id: contentArea
                text: root.initialContent
                placeholderText: qsTr("Текст заметки...")
                font.pixelSize: 16
                wrapMode: TextEdit.Wrap
                textFormat: TextEdit.PlainText
                width: view.availableWidth
            }
        }
    }
}
