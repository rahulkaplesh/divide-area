import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

import { MatCardModule } from '@angular/material/card';
import { MatButtonModule } from '@angular/material/button';
import { MatExpansionModule } from '@angular/material/expansion';
import { MatGridListModule } from '@angular/material/grid-list';
import {MatFormFieldModule} from '@angular/material/form-field';
import {MatInputModule} from '@angular/material/input';
import { FlexLayoutModule } from '@angular/flex-layout';

import { AngularCesiumModule, AngularCesiumWidgetsModule } from 'angular-cesium';
import { PolygonAreaComponent } from './polygon-area/polygon-area.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { PolygonAreaCardComponent } from './polygon-area-card/polygon-area-card.component';
import { PolygonsEditorService } from 'angular-cesium';

import { PolygonCreationService } from './polygon-creation.service';
import { FontAwesomeModule, FaIconLibrary } from '@fortawesome/angular-fontawesome';
import { faTrashAlt } from '@fortawesome/free-solid-svg-icons';

@NgModule({
  declarations: [
    AppComponent,
    PolygonAreaComponent,
    PolygonAreaCardComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    AngularCesiumModule.forRoot({fixEntitiesShadows: false, customPipes: []}),
    AngularCesiumWidgetsModule,
    BrowserAnimationsModule,
    MatCardModule,
    MatButtonModule,
    MatExpansionModule,
    MatGridListModule,
    MatFormFieldModule,
    MatInputModule,
    FlexLayoutModule,
    FontAwesomeModule
  ],
  providers: [PolygonsEditorService, PolygonCreationService],
  bootstrap: [AppComponent]
})
export class AppModule { 
  constructor(private library: FaIconLibrary) {
    library.addIcons(faTrashAlt);
  }
}
