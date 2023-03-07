function retrieveId(event){
    event.preventDefault();

  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(this.responseText);
      var id = response.siteUserId;
      alert("Your id is: " + id);
      document.getElementById("res").innerHTML = id;
    }
  };

  var email = document.getElementById("email").value;
  var password = document.getElementById("password").value;
  
  xhttp.open("GET", "http://localhost:6060/user/" + email + "/" + password, true);
  xhttp.setRequestHeader("Content-Type", "application/json");
  xhttp.send(JSON.stringify(toSend));
}