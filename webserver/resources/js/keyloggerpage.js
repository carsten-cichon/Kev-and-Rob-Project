/**
 * Author: Keven McDowell
 * Browser script for the keylogger page that displays all the keystroke information.
 */

"use strict";

// Small module I wrote inside the script for making the api calls to the server.
const windowFuncs = {
  /**
   * @function getAllStrokes
   * Function that calls the server to retrieve all of the keystroke data.
   */
  getAllStrokes: () => {
    fetch("http://localhost:8080/getAllKeys") // AJAX Call to the server.
      .then(resp => resp.text()) // Getting the server response and turning it back into json.
      .then(text => JSON.parse(text)) // Had to use a weird way because of some random parsing error.
      .then(keystrokes => {
        const dataTableBody = document.querySelector("tbody");
        keystrokes.forEach(entry => {
          // Building the table from the data returned from the database.
          const newRow = document.createElement("tr"),
            newComputer = document.createElement("td"),
            newKeyStrokes = document.createElement("td"),
            newTimestamp = document.createElement("td"),
            computerText = document.createTextNode(entry.computerName),
            keyStrokeText = document.createTextNode(entry.keystrokes),
            timeStampText = document.createTextNode(entry.timestamp);

          newComputer.appendChild(computerText);
          newKeyStrokes.appendChild(keyStrokeText);
          newTimestamp.appendChild(timeStampText);

          newRow.appendChild(newComputer);
          newRow.appendChild(newKeyStrokes);
          newRow.appendChild(newTimestamp);

          dataTableBody.appendChild(newRow);
        });
      })
      .catch(e => {
        throw new Error(e);
      });
  },
  /**
   * @function getStrokesByName
   * @param {name}
   * -Name of the computer you want to find strokes for.
   * Returns the keystroke data for the computer(s) that match the query string.
   */
  getStrokesByName: name => {
    fetch("http://localhost:8080/searchKeys", { // AJAX Post request with the search parameter as the request body.
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({
        computerName: name
      })
    })
      .then(resp => resp.json())  // Taking the search results and converting them to json.
      .then(keystrokes => {
        const dataTableBody = document.querySelector("tbody"),  // Rebuilding the table using the search results.
          table = document.querySelector("table"),
          submitBtn = document.querySelector("#submitBtn");

        table.removeChild(dataTableBody);

        const newTbody = document.createElement("tbody");

        keystrokes.forEach(entry => {
          const newRow = document.createElement("tr"),
            newComputer = document.createElement("td"),
            newKeyStrokes = document.createElement("td"),
            newTimestamp = document.createElement("td"),
            computerText = document.createTextNode(entry.computerName),
            keyStrokeText = document.createTextNode(entry.keystrokes),
            timeStampText = document.createTextNode(entry.timestamp);

          // Building the html for the results using javascript.
          newComputer.appendChild(computerText);
          newKeyStrokes.appendChild(keyStrokeText);
          newTimestamp.appendChild(timeStampText);

          newRow.appendChild(newComputer);
          newRow.appendChild(newKeyStrokes);
          newRow.appendChild(newTimestamp);

          newTbody.appendChild(newRow);
        });

        table.append(newTbody);
        submitBtn.removeAttribute("disabled");
        submitBtn.textContent = "Search";
      })
      .catch(e => {
        const submitBtn = document.querySelector("#submitBtn");
        alert("Error searching for keystrokes.");
        submitBtn.removeAttribute("disabled");
        submitBtn.textContent = "Search";
      });
  }
};

(() => {
  // Code executed when the page finishes loading the DOMContent.
  window.addEventListener(
    "DOMContentLoaded",
    e => {
      const submitButton = document.querySelector("#submitBtn"),
        searchInput = document.querySelector("#searchInput"),
        dataTable = document.querySelector("#dataTable");

      // Takes the value in the search input and uses it to query the database when the submit button is clicked.
      submitButton.addEventListener("click", e => {
        submitButton.textContent = "Loading.....";
        submitButton.setAttribute("disabled", "true");
        e.preventDefault();
        windowFuncs.getStrokesByName(searchInput.value);
      });

      // Populates the data on the page on load.
      windowFuncs.getAllStrokes();
    },
    false
  );
})();
