<?xml version="1.0" encoding="ISO-8859-1"?>
<ncl id="test_descriptor_fontVariant_1" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="reg1"/>
		</regionBase>
		<descriptorBase>
			<descriptor id="desc1" region="reg1" >
				<descriptorParam name="fontVariant" value="" />
				<descriptorParam name="fontFamily" value="Tiresias" />
				<descriptorParam name="fontSize" value="10" />
			</descriptor>
		</descriptorBase>
	</head>

	<body>
		<port id="port1" component="image1" />
		<media id="image1" src="../../../../text/lorem.txt" descriptor="desc1" />
	</body>
</ncl>