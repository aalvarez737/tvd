<?xml version="1.0" encoding="ISO-8859-1"?>
<ncl id="test_descriptor_bounds_25" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="reg1" left="50%"  >
			    <region id="reg2"/>
			 </region>
		</regionBase>
		<descriptorBase>
			<descriptor id="desc1" region="reg1" />
			<descriptor id="desc2" region="reg2" >
				<descriptorParam name="bounds" value="50%,75%,50%,25%" />
			</descriptor>
		</descriptorBase>

	</head>
	<body>
		<port id="port" component="image" />
		<media id="image" src="../../../../images/blue.jpg" descriptor="desc2" />
	</body>
</ncl>
