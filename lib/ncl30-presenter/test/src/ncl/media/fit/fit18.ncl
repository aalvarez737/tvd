<?xml version="1.0" encoding="ISO-8859-1"?>
<ncl id="test_descriptor_fit_18" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="reg1" width="30%" height="50%"/>
		</regionBase>
		<descriptorBase>
			<descriptor id="desc1" region="reg1">

			</descriptor>
		</descriptorBase>
	</head>
	<body>
		<port id="port1" component="image1" />
		<media id="image1" src="../../../../images/paisaje.jpg" descriptor="desc1" >
				<property name="fit" value="meet"/>
				<property name="width" value="50%"/>
		</media>
	</body>
</ncl>