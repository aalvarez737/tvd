<?xml version="1.0" encoding="ISO-8859-1"?>
<ncl id="test_media_top_22" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="reg1" top="144">
				<region id="reg2" top="144" />
			</region>
		</regionBase>
		<descriptorBase>
			<descriptor id="desc1" region="reg1" >
			</descriptor>
			<descriptor id="desc2" region="reg2" >
				<descriptorParam name="top" value="144" />
			</descriptor>
		</descriptorBase>

	</head>
	<body>
		<port id="port1" component="image1" />
		<media id="image1" src="../../../../images/blue.jpg" descriptor="desc2" >
			<property name="top" value="144"/>
		</media>
	</body>
</ncl>
