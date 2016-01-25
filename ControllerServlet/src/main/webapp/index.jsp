<%--
  Created by IntelliJ IDEA.
  User: trak
  Date: 29.07.2015
  Time: 12:33
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Управление месторасположениями</title>
    <!--Import materialize.css-->
    <link type="text/css" rel="stylesheet" href="${pageContext.request.contextPath}/resources/css/materialize.min.css"
          media="screen,projection"/>

    <!--Let browser know website is optimized for mobile-->
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <script>
            function startSensing(){
                $.ajax({
                    url: '/messageGeneratorControl/control/start',
                    type: 'POST',
                    data: {'start':true},
                    success: function (result) {
                        /*alert("button start clicked result = " + result);*/
                    }
                });            }

            function stopSensing(){
                $.ajax({
                    url: '/messageGeneratorControl/control/stop',
                    type: 'POST',
                    data: {'stop':true},
                    success: function (result) {
                        /*alert("button stop clicked result = " + result);*/
                    }
                });
            }


    </script>
</head>
<body>
<script type="text/javascript" src="${pageContext.request.contextPath}/resources/js/jquery-2.1.1.min.js"></script>
<script type="text/javascript" src="${pageContext.request.contextPath}/resources/js/materialize.min.js"></script>
<script type="text/javascript" src="${pageContext.request.contextPath}/resources/js/init.js"></script>
<nav class="light-blue lighten-1" role="navigation">
</nav>
<div class="section no-pad-bot" id="index-banner">
    <div class="container">
        <br><br>
        <h1 class="header center orange-text">Управление месторасположениями</h1>
        <div class="row center">
            <h5 class="header col s12 light">Limbo</h5>
        </div>
        <div class="row center">
            <a class="waves-effect waves-light btn green" onclick="startSensing();"><i class="material-icons left"></i>Запустить</a>
            <a class="waves-effect waves-light btn red" onclick="stopSensing();"><i class="material-icons right"></i>Остановить</a>
        </div>
        <br><br>

    </div>
</div>

<%--<jsp:include page="/sayhello" flush="true"/>--%>

<jsp:include page="/getStatus" flush="true"/>

</body>
</html>
