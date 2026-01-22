import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    property string noteTitle: ""
    property string noteContent: ""
    property string noteDate: ""
    property int noteId: -1

    title: qsTr("Просмотр")

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
                text: "Edit"
                onClicked: {
                    stackView.push("NoteEditorPage.qml", {
                        noteId: root.noteId,
                        initialTitle: root.noteTitle,
                        initialContent: root.noteContent
                    })
                }
            }
            Item { width: 40 }
        }
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: Math.min(parent.width - 40, 800)
        spacing: 20
        anchors.margins: 20

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 5

            Label {
                text: root.noteTitle
                font.pixelSize: 24
                font.bold: true
                wrapMode: Text.Wrap
                Layout.fillWidth: true
            }

            Label {
                text: root.noteDate
                font.pixelSize: 14
                color: "gray"
            }
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
                text: root.noteContent
                readOnly: true
                textFormat: TextEdit.MarkdownText
                wrapMode: TextEdit.Wrap
                font.pixelSize: 16

                background: null
            }
        }
    }
}
