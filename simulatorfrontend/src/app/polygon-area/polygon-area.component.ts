import { Component, OnDestroy, OnInit } from '@angular/core';

import { PolygonCreationService } from '../polygon-creation.service';

import { Cartesian3, CesiumEvent, MapEventsManagerService, PolygonEditorObservable, PolygonEditUpdate, PolygonsEditorService } from 'angular-cesium';
import { Subscription } from 'rxjs';
import { Area, Point } from '../typings';

import { convertCartesianPointsToDegrees, convertDegreesToCartesianPoints } from '../utilities';

@Component({
  selector: 'app-polygon-area',
  templateUrl: './polygon-area.component.html',
  styleUrls: ['./polygon-area.component.scss'],
  providers: []
})
export class PolygonAreaComponent implements OnInit, OnDestroy {

  polyEdit: PolygonEditorObservable = new PolygonEditorObservable();
  private currentAreaBeingEdited: Area;
  editing: boolean = false;

  areaSelectionChangeSub: Subscription = new Subscription();
  pointsChangedSub: Subscription = new Subscription();

  constructor(private polygonEditor: PolygonsEditorService, private polygonCreationService: PolygonCreationService, private mapEventManagerService: MapEventsManagerService) {
    this.currentAreaBeingEdited = {name: '', points: [], selected: false};
    this.mapEventManagerService.register({ event: CesiumEvent.RIGHT_CLICK }).subscribe((result) => {
      if(this.polyEdit) {
        this.polyEdit.dispose();
        this.polyEdit = undefined as any as PolygonEditorObservable;
        this.startExistingEdit();
      }
    })
  }

  ngOnInit(): void {
    this.areaSelectionChangeSub = this.polygonCreationService.getAreaSelectionChangeEmitter()
      .subscribe((item: Area) => this.updateSelectedEditView(item));
  }

  startNewEdit(): void {
    this.polyEdit = this.polygonEditor.create();
    this.pointsChangedSub = this.polyEdit.subscribe((editUpdate: PolygonEditUpdate) => {
      if (editUpdate.positions !== undefined) {
        let points: Point[] = convertCartesianPointsToDegrees(editUpdate.positions as Cartesian3[]);
        this.currentAreaBeingEdited.points = points;
        console.log("Here i have to update area with: ", this.currentAreaBeingEdited);
      }
    });
  }

  startExistingEdit(): void {
    let points: Cartesian3[] = convertDegreesToCartesianPoints(this.currentAreaBeingEdited.points);
    this.polyEdit = this.polygonEditor.edit(points);
    this.pointsChangedSub = this.polyEdit.subscribe((editUpdate: PolygonEditUpdate) => {
      if (editUpdate.positions !== undefined) {
        let points: Point[] = convertCartesianPointsToDegrees(editUpdate.positions as Cartesian3[]);
        this.currentAreaBeingEdited.points = points;
        console.log("Here i have to update area with: ", this.currentAreaBeingEdited);
      }
    });
  }

  updateSelectedEditView(area: Area) {
    if (this.currentAreaBeingEdited !== area){
      this.currentAreaBeingEdited = area;
      this.pointsChangedSub.unsubscribe();
      if (this.editing) {
        this.polyEdit.dispose();
      }
    }
    if (this.currentAreaBeingEdited.selected === false) {
      this.polyEdit.dispose();
      this.pointsChangedSub.unsubscribe();
      this.editing = false;
    } else {
      this.editing = true;
      if (this.currentAreaBeingEdited.points.length === 0) {
        this.startNewEdit();
      } else {
        this.startExistingEdit();
      }
    }
  }

  ngOnDestroy(): void{
    this.areaSelectionChangeSub.unsubscribe();
  }

}
