import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root
    title: qsTr("Мои заметки")

    header: ToolBar {
        Label {
            text: root.title
            anchors.centerIn: parent
            font.pixelSize: 20
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: notesModel
        spacing: 10
        clip: true

        delegate: ItemDelegate {
            width: listView.width
            height: 80

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 15
                spacing: 5

                Label {
                    text: model.title
                    font.bold: true
                    font.pixelSize: 16
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }

                Label {
                    text: model.date
                    font.pixelSize: 12
                    color: "gray"
                }
            }

            Button {
                text: "X"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 10
                flat: true
                onClicked: {
                    notesModel.removeNote(index)
                }
            }

            onClicked: {
                stackView.push("NoteViewPage.qml", {
                    noteTitle: model.title,
                    noteContent: model.content,
                    noteDate: model.date
                })
            }
        }
    }

    RoundButton {
        text: "+"
        font.pixelSize: 24
        width: 60
        height: 60
        radius: 30
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        highlighted: true

        onClicked: {
            stackView.push("NoteEditorPage.qml")
        }
    }
}
