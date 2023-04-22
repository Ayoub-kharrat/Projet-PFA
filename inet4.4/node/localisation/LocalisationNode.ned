//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.node.localisation;
import inet.node.aodv.AodvRouter;
import inet.routing.localisation.Localisation;






 module LocalisationNode extends AodvRouter
 {
     parameters:
         string type=default("target");
         double n=default(0.3);
         double rssiRef=default(-60);
         
    submodules:
        localisation: Localisation {
            @display("p=825,226");
        }
    connections:
        localisation.socketOut --> at.in++;
        localisation.socketIn <-- at.out++;
}
