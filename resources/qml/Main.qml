import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 400
    height: 700
    visible: true
    title: qsTr("Giga Notes")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: NoteListPage {}
    }
}
