<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <html>
      <head>
        <link rel="stylesheet" type="text/css" href="style.css"/>
      </head>
      <body>
        <h2>Vorlesungen</h2>
        <table border="1">
          <xsl:for-each select="Vorlesung">
            <tr>
              <td><xsl:value-of select="Titel"/></td>
              <td><xsl:value-of select="Semester"/></td>
              <td><xsl:value-of select="Hochschule"/></td>
              <td><xsl:value-of select="SWS"/></td>
              <td>
                <table border="1">
                  <xsl:for-each select="./Kapitel">
                    <tr>
                      <td><xsl:value-of select="."/></td>
                    </tr>
                  </xsl:for-each>
                </table>
              </td>
            </tr>
          </xsl:for-each>
        </table>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>
