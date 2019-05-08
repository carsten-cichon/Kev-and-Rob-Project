/**
 * Author: Keven McDowell
 * Browser script for the keylogger page that displays all the keystroke information.
 */

"use strict";

// Small module I wrote inside the script for making the api calls to the server.
const windowFuncs = {
  // Function for grabbing all of the keystroke data from the server and building a table on the page
  // with it.
  /**
   * @function getAllStrokes
   * Function that calls the server to retrieve all of the keystroke data.
   */
  getAllStrokes: () => {
    fetch("http://localhost:8080/getAllKeys")
      .then(resp => resp.text())
      .then(text => JSON.parse(text))
      .then(keystrokes => {
        keystrokes.forEach(entry => {
          const dataTableBody = document.querySelector("tbody"),
            newRow = document.createElement("tr"),
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
    fetch("http://localhost:8080/searchKeys", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({
        computerName: name
      })
    })
      .then(resp => resp.json())
      .then(keystrokes => {
        const dataTableBody = document.querySelector("tbody"),
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
          console.log(entry);
          // Building the html for the results.

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

      // Event listener to query the database on the server when clicked.
      submitButton.addEventListener("click", e => {
        submitButton.textContent = "Loading.....";
        submitButton.setAttribute("disabled", "true");
        e.preventDefault();
        console.log(searchInput.value);
        windowFuncs.getStrokesByName(searchInput.value);
      });

      // Event listener for the input that the computer name is entered into.
      searchInput.addEventListener("input", e => {
        e.preventDefault();
      });

      // Populates the data on the page on load.
      windowFuncs.getAllStrokes();
    },
    false
  );
})();
