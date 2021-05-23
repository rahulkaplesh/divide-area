import { Component } from '@angular/core';

import { ViewerConfiguration } from 'angular-cesium';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
  providers: [ViewerConfiguration],
})
export class AppComponent {
  title = 'simulatorfrontend';

  constructor(private viewerConf: ViewerConfiguration) {
    viewerConf.viewerOptions = {
      selectionIndicator: false,
      timeline: false,
      infoBox: false,
      fullscreenButton: false,
      baseLayerPicker: false,
      animation: false,
      shouldAnimate: false,
      homeButton: false,
      geocoder: false,
      scene3DOnly: true,
      navigationHelpButton: false,
      navigationInstructionsInitiallyVisible: false,
      imageryProvider: new Cesium.BingMapsImageryProvider({
        url : 'https://dev.virtualearth.net',
        key: 'AmL2tQokxYaKGlIn_y1FF7eR3NsGmreYY8BiLYsCBGVYVPTksjK5j3dQg5NfGUwJ',
        mapStyle: Cesium.BingMapsStyle.AERIAL_WITH_LABELS  
    }),
    };
  }
}
