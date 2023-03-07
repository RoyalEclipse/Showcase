class registerData {
  constructor(name, surname, email, phoneNumber, credits, password) {
    this.name = name;
    this.surname = surname;
    this.email = email;
    this.phoneNumber = phoneNumber;
    this.credits = credits;
    this.password = password;
  }
}


function sendData(event) {
  event.preventDefault();
  var toSend = new registerData();
  toSend.name = document.getElementById("name").value;
  toSend.surname = document.getElementById("surname").value;
  toSend.email = document.getElementById("email").value;
  toSend.phoneNumber = document.getElementById("phone").value;
  toSend.credits = document.getElementById("credits").value;
  toSend.password = document.getElementById("password").value;

  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var response = JSON.parse(this.responseText);
      var id = response.id;
      alert("Your id is: " + id);
      document.getElementById("res").innerHTML = id;
    }
  };
  xhttp.open("POST", "http://localhost:6060/user", true);
  xhttp.setRequestHeader("Content-Type", "application/json");
  xhttp.send(JSON.stringify(toSend));
}