import { Component, EventEmitter, OnDestroy, OnInit } from '@angular/core';

import { Area } from '../typings';

import { PolygonCreationService } from '../polygon-creation.service';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-polygon-area-card',
  templateUrl: './polygon-area-card.component.html',
  styleUrls: ['./polygon-area-card.component.scss'],
  providers: []
})
export class PolygonAreaCardComponent implements OnInit, OnDestroy {

  areaListView: Area[] = [];

  areaListChangeSubscription: Subscription = new Subscription();

  constructor(private createPolygonService: PolygonCreationService) { }

  ngOnInit(): void {
    this.areaListChangeSubscription = this.createPolygonService.getAreaListChangeEmitter()
      .subscribe((item: Area[]) => this.updateViewAreaList(item));
  }

  addAnArea(): void {
    this.createPolygonService.addArea();
  }

  updateViewAreaList(areaList: Area[]) {
    this.areaListView = areaList;
  }

  onSelected(areaSelected: Area): void {
    this.areaListView.map( (area: Area) => {
      if (areaSelected !== area) {
        area.selected =false;
      } else {
        area.selected =true;
      }
    });
    this.createPolygonService.selectedAreaChanged(areaSelected);
  }

  unSelected(areaSelected: Area): void {
    if (areaSelected.selected === true) {
      areaSelected.selected = false;
      this.createPolygonService.selectedAreaChanged(areaSelected);
    }

  }

  ngOnDestroy(): void {
    this.areaListChangeSubscription.unsubscribe();
  }

}
