import QtQuick 2.4

Rectangle {
    width: 180; height: 200


    Component {
        id: projectDelegate
        Item {
		width: 180; height: 50
		Column {
                	Text { text: '<b>Title:</b> ' + title }
                	Text { text: '<b>Desciption</b> ' + description }
                	Text { text: '<b>Owner</b> ' + owner }
            	}
        }
    }



    ListView {
        width: 180; height: 200
        model: ProjectListModel {}
        delegate: projectDelegate
        focus: true
    }
}

