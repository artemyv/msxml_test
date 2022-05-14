<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
                version="1.0">
<xsl:template match="/">
<HTML>
  <BODY>
    <TABLE BORDER="2">
      <TR>
        <TD>Symbol</TD>
        <TD>Name</TD>
        <TD>Price</TD>
      </TR>
      <!-- Use xsl:apply-templates. -->
      <xsl:apply-templates select="portfolio/stock">
      <!-- Sort by stock symbols. -->
        <xsl:sort select="symbol"/>
      </xsl:apply-templates>      
    </TABLE>

  </BODY>
</HTML>
</xsl:template>

<xsl:template match="portfolio/stock">
  <xsl:for-each-group select='entry' group-by='fn:concat(
    if (fn:matches(dxp:dimension[@name="ga:pagePath"]/@value, "^/sales"))
      then "/sales"
      else "non-/sales",
    " referred from ",
    if (fn:matches(dxp:dimension[@name="ga:referralPath"]/@value, "^/forsale"))
      then "/forsale"
      else "non-/forsale"
    )'>
    <tr>
      <td><xsl:value-of select='../dxp:tableName'/></td>
      <td>
        <xsl:value-of select='../dxp:startDate'/>-<xsl:value-of select='../dxp:endDate'/>
      </td>
      <td><xsl:value-of select='current-grouping-key()'/></td>
      <td><xsl:value-of select="sum(current-group()/dxp:metric/@value)"/></td>
    </tr>
  </xsl:for-each-group>
      <TR>
   <!-- Use xsl:choose and xsl:when. -->
   <xsl:attribute name="STYLE">color:
     <xsl:choose>
            <xsl:when test="price[. &lt; 30]">green</xsl:when>
            <xsl:when test="price[. &gt; 50]">red</xsl:when>
     </xsl:choose>
   </xsl:attribute>

   <!-- Generate an attribute as a tooltip of TR. -->
   <xsl:attribute name="Title"><xsl:value-of select="symbol"/> is listed on the <xsl:value-of select="@exchange"/> stock exchange.</xsl:attribute>
        <TD><xsl:value-of select="symbol"/>
   <!-- Use xsl:if. -->
    <xsl:if test="@exchange[.='nasdaq']">*</xsl:if></TD>              
        <TD><xsl:value-of select="name"/></TD>
        <TD><xsl:value-of select="price"/></TD>
      </TR>
      </xsl:template>
</xsl:stylesheet>
