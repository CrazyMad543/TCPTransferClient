import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import Client.data 1.0

ApplicationWindow {
    visible: true
    width: 600
    height: 210
    title: qsTr("Transfer Client")

    Label {
        id: fileLabel
        text: qsTr("File: ")
        font.pixelSize: 20
        height: 30
        anchors {
            left: parent.left
            top: parent.top
            leftMargin: 10
            topMargin: 10
        }
    }

    TextField {
        id: fileUrl
        text: qsTr(clientData.filePath)
        readOnly: true
        height: 30
        font.pixelSize: 18
        anchors {
            left: fileLabel.right
            top: parent.top
            right: selectButton.left
            rightMargin: 10
            topMargin: 10
        }
    }

    Button {
        id: selectButton
        text: qsTr("Select file")
        height: 30
        font.pixelSize: 20
        anchors {
            right: parent.right
            top: parent.top
            rightMargin: 10
            topMargin: 10
        }
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: "Please select a file"
        visible: false
        folder: shortcuts.desktop
        onAccepted: {
            clientData.openFile(fileDialog.fileUrl)
            fileDialog.close();
        }
    }

    Label {
        id: sizeLabel
        text: qsTr("Size: " + clientData.sizeFile)
        font.pixelSize: 20
        height: 30
        anchors {
            left: parent.left
            top: fileLabel.bottom
            leftMargin: 10
            topMargin: 10
        }
    }

    Label {
        id: hostLabel
        text: qsTr("Host: ")
        height: 30
        font.pixelSize: 20
        anchors {
            left: parent.left
            top: sizeLabel.bottom
            leftMargin: 10
            topMargin: 10
        }
    }

    TextField {
        id: hostIp
        height: 30
        width: 155
        font.pixelSize: 18
        inputMask: "000.000.000.000;_"
        anchors {
            left: hostLabel.right
            top: sizeLabel.bottom
            topMargin: 10
        }
    }

    Label {
        id: portLabel
        text: qsTr("Port: ")
        font.pixelSize: 20
        anchors {
            top: sizeLabel.bottom
            right: portNumber.left
            rightMargin: 10
            topMargin: 10
        }
    }

    TextField {
        id: portNumber
        height: 30
        width: 70
        font.pixelSize: 18
        validator: IntValidator {
            bottom: 0
            top: 65535
        }
        anchors {
            right: parent.right
            top: sizeLabel.bottom
            rightMargin: 10
            topMargin: 10
        }
    }

    Label {
        id: progressLabel
        text: qsTr("Progress")
        height: 30
        font.pixelSize: 20
        anchors {
            left: parent.left
            top: hostLabel.bottom
            leftMargin: 10
            topMargin: 10
        }
    }

    Button {
        id: transferButton
        text: qsTr("Transfer")
        height: 30
        width: 100
        font.pixelSize: 20
        anchors {
            right: parent.right
            top: portNumber.bottom
            rightMargin: 10
            topMargin: 10
        }
        onClicked: clientData.sendFile(hostIp.text, portNumber.text)
    }

    ProgressBar {
        id: progressTransfer
        value: clientData.value

        anchors {
            top: progressLabel.bottom
            left: parent.left
            right: parent.right
            topMargin: 10
            leftMargin: 10
            rightMargin: 10
        }
        background: Rectangle {
                implicitHeight: 30
                color: "#e6e6e6"
                radius: 10
            }
    }

    ClientData {
        id: clientData
    }

}
