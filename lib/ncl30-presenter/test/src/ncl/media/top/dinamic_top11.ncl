<?xml version="1.0" encoding="ISO-8859-1"?>
<ncl id="test_media_dinamic_top_11" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="reg" />
		</regionBase>
		<descriptorBase>
			<descriptor id="desc" region="reg" />
		</descriptorBase>
		<connectorBase>
			<importBase documentURI="../../conectores.ncl" alias="con"/>
		</connectorBase>
	</head>
	<body>
		<port id="port" component="image" />
		<media id="image" src="../../../../images/blue.jpg" descriptor="desc" >
			<property name="top" value="600" />
		</media>
		<link xconnector="con#onRedSelectionSet">
			<bind component="image" role="onSelection"/>
			<bind component="image" role="set" interface="top" >
				<bindParam name="value" value="288"/>
			</bind>
		</link>
	</body>
</ncl>
