<?xml version="1.0" encoding="ISO-8859-1"?>
<ncl id="test_descriptor_width_16" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="reg1"  width="40PX"/>
		</regionBase>
		<descriptorBase>
			<descriptor id="desc1" region="reg1">
			      <descriptorParam name="" value=""/>
			</descriptor>
		</descriptorBase>
	</head>
	<body>
		<port id="port1" component="image1" />
		<media id="image1" src="../../../../images/blue.jpg" descriptor="desc1" />
	</body>
</ncl>