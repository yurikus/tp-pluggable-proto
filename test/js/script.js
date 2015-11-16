$(document).ready(
  function()
  {
    window.XMLHttpRequest = new window.ActiveXObject("Microsoft.XMLHTTP");

    $("#log").ajaxError(function(e, jqxhr, settings, err)
    {
        var vDebug = "<pre>";
        for (var prop in err)
            vDebug += "property: '" + prop + "' value: ["+ err[prop]+ "]\n";
        vDebug += "toString(): " + " value: [" + err.toString() + "]</pre>";

        $(this).html(vDebug);
    });

    $("#btnXHR").click(function(e)
    {
      $.ajax(
      {
        url: "ajax.html",
        success: function()
        {
          $("#divAJAX").html();
        },
        error: function(xhr)
        {
          $("#divAJAX").html(xhr.responseText);
        }
      });
    });
});
