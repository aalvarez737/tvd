<?xml version="1.0" encoding="ISO-8859-1"?>
<!-- Generated by NCL Eclipse -->
<ncl id="explicitDur_DescriptorsTest" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
			<regionBase>
				<region id="img1Reg" height="40%" top="0%" width="80%" left="10%"/>
				<region id="img2Reg" height="40%" top="50%" width="80%" left="10%"/>
			</regionBase>
			<descriptorBase>
				<descriptor id="img1Desc" region="img1Reg" explicitDur="4s"/>
				<descriptor id="img2Desc" region="img2Reg" explicitDur="7s"/>
			</descriptorBase>
	</head>

	<body>
		<port id="p0" component="img1"/>
		<port id="p1" component="img2"/>
		<media id="img1" src="../resources/images/lifia.jpg" descriptor="img1Desc" />
		<media id="img2" src="../resources/images/lifia.jpg" descriptor="img2Desc" />
	</body>
</ncl>
