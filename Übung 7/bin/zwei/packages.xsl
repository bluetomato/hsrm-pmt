<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="/">
		<html><head><title>Packages und Klassen</title></head><body>
			<xsl:apply-templates/>
		</body></html>
	</xsl:template>
	
	<xsl:template match="kurztitel">
	</xsl:template>
	
	<xsl:template match="titelseite">
	</xsl:template>

	<xsl:template match="skript">
		<xsl:for-each select="/descendant::anhang//code">
			<br/>Klasse: 
			<xsl:value-of select="@class"/>
			<br/>Packet:
			<xsl:value-of select="@package"/>
			<br/>---------------------------------------------------------------------------------------
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>